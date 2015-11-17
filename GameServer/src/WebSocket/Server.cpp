///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/Server.hpp"
#include "WebSocket/Connection.hpp"
#include "WebSocket/SubProtocol.hpp"
#include "Database/StoredProcedures.hpp"
#include "utility.hpp"
using namespace WebSocket;
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

Server::Server(unsigned int port, const std::vector<const SubProtocol*>& protocols, SslData sslData)
: mVerbose(false)
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

    info.ssl_cert_filepath = sslData.certPath;
    info.ssl_ca_filepath = sslData.caPath;
    info.ssl_private_key_filepath = sslData.privateKeyPath;
    info.ssl_private_key_password = sslData.privateKeyPassword;

    mContext = libwebsocket_create_context(&info);

    if (!mContext)
        throw std::runtime_error("Could not initialize WebSocket server.");
}

///////////////////////////////////

libwebsocket_protocols* Server::initializeProtocols(const std::vector<const SubProtocol*>& protocols)
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

void Server::addClient(Connection* client)
{
    std::unordered_map<std::string, Connection*>& clients = mClients[client->getProtocolId()];
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

void Server::removeClient(Connection& client)
{
    mClients[client.getProtocolId()].erase(client.getUsername());
}

///////////////////////////////////

void Server::removeClient(std::unordered_map<std::string, Connection*>::iterator it)
{
    mClients[it->second->getProtocolId()].erase(it);
}

///////////////////////////////////

const std::unordered_map<std::string, Connection*>& Server::getClients(unsigned int protocolId) const
{
    return mClients[protocolId];
}

///////////////////////////////////

Server::~Server()
{
    libwebsocket_context_destroy(mContext);
}

///////////////////////////////////

void Server::run()
{
    while(true)
    {
        libwebsocket_service(mContext, 50);
    }
}

///////////////////////////////////

Server::ResponseCode Server::validateUserCredentials(std::string username, std::string password) const
{
    std::string hashedPassword;
    std::string salt;

    Database::StoredProcedures::GET_USER_CREDENTIALS.call(username, hashedPassword, salt);

    if(sha512(password + salt) == hashedPassword)
        return ResponseCode::Success;
    else
        return ResponseCode::InvalidUserCredentials;


    return ResponseCode::Success;
}

///////////////////////////////////

std::string Server::getIp(libwebsocket* webSocketInstance) const
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

Server::ResponseCode Server::handleConnectionRequest(void* connectionData, libwebsocket* webSocketInstance)
{
    std::string username, password;
    if(!SubProtocol::getUserCredentials(webSocketInstance, username, password))
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
        SubProtocol::createConnection(username, connectionData, webSocketInstance, *this);
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

void Server::handleConnectionOpen(void* connectionData)
{
    Connection* connection = &SubProtocol::getConnection(connectionData);
    addClient(connection);

    if(mVerbose)
        std::cout << "'" << connection->getUsername() << "' has connected from " << connection->getIp() << " with the '" << connection->getProtocolName() << "' protocol." << std::endl;
}

///////////////////////////////////

void Server::handleConnectionClosed(void* connectionData)
{
    Connection& connection = SubProtocol::getConnection(connectionData);
    removeClient(connection);

    if(mVerbose)
        std::cout << "'" << connection.getUsername() << "' has disconnected." << std::endl;
}

///////////////////////////////////

 void Server::setVerbose(bool flag)
 {
     mVerbose = flag;
 }

///////////////////////////////////

void Server::broadcastString(std::string message, unsigned int protocolId, std::list<std::string> excludeUsers) const
{
    for(const std::pair<std::string, Connection*>& client : mClients[protocolId])
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

void Server::broadcastLines(std::vector<std::string> lines, unsigned int protocolId, std::list<std::string> excludeUsers) const
{
    std::ostringstream stream;
    for(std::string& line : lines)
        stream << line << '\n';

    broadcastString(stream.str(), protocolId, excludeUsers);
}

///////////////////////////////////

void Server::closeDeadConnections()
{
    time_t currentTime;
    time(&currentTime);

    for(std::unordered_map<std::string, Connection*>& protocol : mClients)
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
