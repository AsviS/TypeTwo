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
{
    lws_set_log_level
    (
        LLL_ERR | LLL_NOTICE,
        NULL
    );




    lws_context_creation_info info;
    memset(&info, 0, sizeof info);

    info.port = port;


    info.protocols =  initializeProtocols(protocols);
    info.extensions = libwebsocket_get_internal_extensions();
    info.gid = -1;
    info.uid = -1;
    info.user = this;

    mContext = libwebsocket_create_context(&info);


    if (!mContext)
        throw std::runtime_error("Could not initialize WebSocket server.");
}

///////////////////////////////////

libwebsocket_protocols* WebSocketServer::initializeProtocols(const std::vector<const WebSocketSubProtocol*>& protocols)
{

    unsigned int size = protocols.size() + 2;
    libwebsocket_protocols* libwebsocketProtocols = new libwebsocket_protocols[size];

    libwebsocketProtocols[0] =
    {
        "http-only",
        [](libwebsocket_context * context, libwebsocket* webSocketInstance, libwebsocket_callback_reasons reason, void* connectionData, void* in, size_t len)
        {
            return 0;
        },
        0
    };

    for(unsigned int i = 1; i < size - 1; i++)
        libwebsocketProtocols[i] = protocols[i - 1]->toLibWebSocketProtocol();

    libwebsocketProtocols[size - 1] = {nullptr, nullptr, 0};

    mClients.resize(size);

    return libwebsocketProtocols;
}

///////////////////////////////////

void WebSocketServer::addClient(WebSocketConnection* client)
{
    std::unordered_map<std::string, WebSocketConnection*>& clients = mClients[client->getProtocolId()];
    auto it = clients.find(client->getUsername());

    if(it != clients.end())
    {
        if(mVerbose)
            std::cout << "'" << client->getUsername() << "' already logged in at " << client->getIp() << " with the same protocol. Kicking existing user." << std::endl;

        it->second->silentClose();
        it->second = client;
    }
    else
        clients[client->getUsername()] = client;
}

///////////////////////////////////

void WebSocketServer::removeClient(WebSocketConnection& client)
{
    mClients[client.getProtocolId()].erase(client.getUsername());
}

///////////////////////////////////

void WebSocketServer::removeClient(std::unordered_map<std::string, WebSocketConnection*>::iterator it)
{
    mClients[it->second->getProtocolId()].erase(it);
}

///////////////////////////////////

const std::unordered_map<std::string, WebSocketConnection*>& WebSocketServer::getClients(unsigned int protocolId) const
{
    return mClients[protocolId];
}

///////////////////////////////////

WebSocketServer::~WebSocketServer()
{
    libwebsocket_context_destroy(mContext);
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
        std::cout << "'" << connection->getUsername() << "' has connected from " << connection->getIp() << " with the '" << connection->getProtocolName() << "' protocol." << std::endl;
}

///////////////////////////////////

void WebSocketServer::handleConnectionClosed(void* connectionData)
{
    WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);
    removeClient(connection);

    if(mVerbose)
        std::cout << "'" << connection.getUsername() << "' has disconnected." << std::endl;
}

///////////////////////////////////

 void WebSocketServer::setVerbose(bool flag)
 {
     mVerbose = flag;
 }

///////////////////////////////////

void WebSocketServer::broadcastString(std::string message, unsigned int protocolId, std::list<std::string> excludeUsers) const
{
    for(const std::pair<std::string, WebSocketConnection*>& client : mClients[protocolId])
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

void WebSocketServer::broadcastLines(std::vector<std::string> lines, unsigned int protocolId, std::list<std::string> excludeUsers) const
{
    std::ostringstream stream;
    for(std::string& line : lines)
        stream << line << '\n';

    broadcastString(stream.str(), protocolId, excludeUsers);
}

///////////////////////////////////

void WebSocketServer::closeDeadConnections()
{
    time_t currentTime;
    time(&currentTime);

    for(std::unordered_map<std::string, WebSocketConnection*>& protocol : mClients)
    {
        auto it = protocol.begin();
        while(it != protocol.end())
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

}
