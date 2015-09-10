///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketServer.hpp"
#include "WebSocketSubProtocol.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <stdexcept>
#include <iostream>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////


WebSocketServer::WebSocketServer(unsigned int port, const std::vector<const WebSocketSubProtocol*>& protocols)
: mVerbose(false)
{
    lws_context_creation_info info;
    memset(&info, 0, sizeof info);

    info.port = port;

    initializeProtocols(protocols);
    info.protocols = mProtocols;
    info.extensions = libwebsocket_get_internal_extensions();
    info.gid = -1;
    info.uid = -1;

    info.user = this;

    mContext = libwebsocket_create_context(&info);


    if (!mContext)
        throw std::runtime_error("Could not initialize WebSocket server.");
}

///////////////////////////////////

void WebSocketServer::initializeProtocols(const std::vector<const WebSocketSubProtocol*>& protocols)
{

    unsigned int size = protocols.size() + 2;
    mProtocols = new libwebsocket_protocols[size];

    mProtocols[0] =
    {
        "http-only",
        [](libwebsocket_context * context, libwebsocket* webSocketInstance, libwebsocket_callback_reasons reason, void* connectionData, void* in, size_t len)
        {
            return 0;
        },
        0
    };

    for(unsigned int i = 1; i < size - 1; i++)
        mProtocols[i] = protocols[i - 1]->toLibWebSocketProtocol();

    mProtocols[size - 1] = {nullptr, nullptr, 0};
}

///////////////////////////////////

void WebSocketServer::addClient(WebSocketConnection client)
{
    mClients.insert(std::make_pair(client.getUsername(), client));
}

///////////////////////////////////

bool WebSocketServer::userIsConnected(std::string username) const
{
    return mClients.find(username) != mClients.end();
}

///////////////////////////////////

void WebSocketServer::removeClient(std::string username)
{
    mClients.erase(username);
}


///////////////////////////////////

const std::map<std::string, WebSocketConnection>& WebSocketServer::getClients() const
{
    return mClients;
}

///////////////////////////////////

WebSocketServer::~WebSocketServer()
{
    libwebsocket_context_destroy(mContext);
    delete[] mProtocols;
}

///////////////////////////////////

void WebSocketServer::run()
{
    while(true)
        libwebsocket_service(mContext, 50);
}

///////////////////////////////////

WebSocketServer::ResponseCode WebSocketServer::validateConnection(const WebSocketConnection& connection) const
{
    std::string username = connection.getUsername();
    //if(username != "bob" && username != "karl")
       // return ResponseCode::InvalidUserCredentials;

    if(userIsConnected(username))
        return ResponseCode::UserAlreadyLoggedIn;

    return ResponseCode::Success;
}

///////////////////////////////////

std::string WebSocketServer::getIp(libwebsocket* webSocketInstance) const
{
    unsigned int BUFFER_SIZE = 50;
    char* ipBuffer = new char[BUFFER_SIZE];
    memset(ipBuffer, 0, BUFFER_SIZE);

    libwebsockets_get_peer_addresses(mContext, webSocketInstance, libwebsocket_get_socket_fd(webSocketInstance), ipBuffer, 0, ipBuffer, BUFFER_SIZE);

	std::string ip(ipBuffer);
	delete[] ipBuffer;

	return ip;
}

///////////////////////////////////

WebSocketServer::ResponseCode WebSocketServer::handleConnectionRequest(void* connectionData, libwebsocket* webSocketInstance) const
{
    WebSocketConnection& connection = WebSocketSubProtocol::createConnection(connectionData, webSocketInstance, *this);
    ResponseCode response = validateConnection(connection);

    if(mVerbose && response != ResponseCode::Success)
    {
        std::cout << "Connection from " << connection.getIp() << " refused. Reason: ";
        switch(response)
        {
            case ResponseCode::InvalidUserCredentials:
                std::cout << "Invalid user credentials" << std::endl;
                break;

            case ResponseCode::UserAlreadyLoggedIn:
                std::cout << "User is already logged in" << std::endl;

                default:
                    break;
        }
    }

    return response;
}

///////////////////////////////////

void WebSocketServer::handleConnectionOpen(void* connectionData)
{
    WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);
    addClient(connection);

    if(mVerbose)
        std::cout << "'" << connection.getUsername() << "' has connected from " << connection.getIp() << "." << std::endl;
}

///////////////////////////////////

void WebSocketServer::handleConnectionClosed(void* connectionData)
{
    WebSocketConnection connection = WebSocketSubProtocol::getConnection(connectionData);
    removeClient(connection.getUsername());

    if(mVerbose)
        std::cout << "'" << connection.getUsername() << "' has disconnected." << std::endl;
}

///////////////////////////////////

 void WebSocketServer::setVerbose(bool flag)
 {
     mVerbose = flag;
 }
