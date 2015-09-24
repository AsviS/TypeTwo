///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketServer.hpp"
#include "WebSocketSubProtocol.hpp"
#include "UserProvider.hpp"
#include "utility.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////

WebSocketServer::WebSocketServer(unsigned int port, const std::vector<const WebSocketSubProtocol*>& protocols, Database& db)
: mVerbose(false)
, mDb(db)
, mNumProtocols(protocols.size())
{
    lws_set_log_level
    (
        LLL_ERR | LLL_NOTICE,
        NULL
    );




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

void WebSocketServer::addClient(WebSocketConnection* client)
{
    auto it = mClients.find(client->getUsername());

    if(it != mClients.end())
    {
        if(mVerbose)
            std::cout << "'" << client->getUsername() << "' already logged in at " << client->getIp() << ". Kicking existing user." << std::endl;

        it->second->silentClose();
        it->second = client;
    }
    else
        mClients[client->getUsername()] = client;
}

///////////////////////////////////

void WebSocketServer::removeClient(std::string username)
{
    mClients.erase(username);
}

///////////////////////////////////

void WebSocketServer::removeClient(std::map<std::string, WebSocketConnection*>::iterator it)
{
    mClients.erase(it);
}

///////////////////////////////////

const std::map<std::string, WebSocketConnection*>& WebSocketServer::getClients() const
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
    {
        libwebsocket_service(mContext, 50);
    }
}

///////////////////////////////////


WebSocketServer::ResponseCode WebSocketServer::validateUserCredentials(std::string username, std::string password) const
{
    std::string hashedPassword;
    std::string salt;

    UserProvider userProvider(mDb);
    userProvider.getCredentials(username, hashedPassword, salt);

    if(sha512(password + salt) == hashedPassword)
        return ResponseCode::Success;
    else
        return ResponseCode::InvalidUserCredentials;


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

WebSocketServer::ResponseCode WebSocketServer::handleConnectionRequest(void* connectionData, libwebsocket* webSocketInstance)
{
    std::string username, password;
    if(!WebSocketSubProtocol::getUserCredentials(webSocketInstance, username, password))
    {
        if(mVerbose)
        {
            std::cout << "Connection from " << getIp(webSocketInstance) << " refused. Reason: ";
            std::cout << "Invalid formatting of user credentials in request's GET URI." << std::endl;
        }

        return ResponseCode::InvalidUserCredentials;
    }

    ResponseCode response = validateUserCredentials(username, password);

    if(response == ResponseCode::Success)
        WebSocketSubProtocol::createConnection(username, connectionData, webSocketInstance, *this);
    else if(mVerbose)
    {
        std::cout << "Connection from " << getIp(webSocketInstance) << " refused. Reason: ";
        switch(response)
        {
            case ResponseCode::InvalidUserCredentials:
                std::cout << "Invalid user credentials" << std::endl;
                break;
            default:
                break;
        }
    }

    return response;
}

///////////////////////////////////

void WebSocketServer::handleConnectionOpen(void* connectionData)
{
    WebSocketConnection* connection = &WebSocketSubProtocol::getConnection(connectionData);
    addClient(connection);

    if(mVerbose)
        std::cout << "'" << connection->getUsername() << "' has connected from " << connection->getIp() << "." << std::endl;
}

///////////////////////////////////

void WebSocketServer::handleConnectionClosed(void* connectionData)
{
    WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);
    removeClient(connection.getUsername());

    if(mVerbose)
        std::cout << "'" << connection.getUsername() << "' has disconnected." << std::endl;
}

///////////////////////////////////

 void WebSocketServer::setVerbose(bool flag)
 {
     mVerbose = flag;
 }

///////////////////////////////////

void WebSocketServer::broadcastString(std::string message, std::list<std::string> excludeUsers) const
{
    for(const std::pair<std::string, WebSocketConnection*>& client : mClients)
    {
        if(excludeUsers.size() > 0)
        {
            auto found = std::find(excludeUsers.begin(), excludeUsers.end(), client.second->getUsername());
            if(found == excludeUsers.end())
                client.second->sendString(message);
            else
                excludeUsers.erase(found);
        }
        else
            client.second->sendString(message);
    }

}

///////////////////////////////////

void WebSocketServer::broadcastLines(std::vector<std::string> lines) const
{
    std::ostringstream stream;
    for(std::string& line : lines)
        stream << line << '\n';

    broadcastString(stream.str());
}

///////////////////////////////////

void WebSocketServer::closeDeadConnections()
{
    time_t currentTime;
    time(&currentTime);

    auto it = mClients.begin();
    while(it != mClients.end())
    {
        if(currentTime - it->second->getLastAliveTime() > 60)
        {
            it->second->silentClose();
            removeClient(it++);
        }
        else
            it++;
    }
}
