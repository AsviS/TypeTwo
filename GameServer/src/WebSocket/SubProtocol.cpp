///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/SubProtocol.hpp"
#include "WebSocket/Connection.hpp"
#include "WebSocket/Server.hpp"
#include "utility.hpp"
using namespace WebSocket;
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
#include <stdexcept>
///////////////////////////////////


SubProtocol::SubProtocol(std::string name, int sessionDataSize, callback_function* callback)
: M_NAME(name)
, M_SESSION_DATA_SIZE(sessionDataSize)
, M_CALLBACK(callback)
{
}

///////////////////////////////////

libwebsocket_protocols SubProtocol::toLibWebSocketProtocol() const
{
    return
    {
        stringToChar(M_NAME),
        M_CALLBACK,
        M_SESSION_DATA_SIZE
    };
}

///////////////////////////////////

Server& SubProtocol::getServer(libwebsocket_context* context)
{
    return *((Server*)libwebsocket_context_user(context));
}

///////////////////////////////////

Connection& SubProtocol::getConnection(void* connectionData)
{
    Connection* connection = (*(Connection**)connectionData);

    if(connection == nullptr)
        throw std::runtime_error("DEVELOPMENT ERROR: \nA connection has been established without having its connection data initialized. This may be caused by an invalid protocol that does not use the standard protocol properly. See existing protocols for examples. \n");

    return *(*(Connection**)connectionData);
}

///////////////////////////////////

Connection& SubProtocol::createConnection(std::string username, void* connectionData, libwebsocket* webSocketInstance, const Server& server)
{
    Connection* connection = new Connection(username, webSocketInstance, server);
    *(Connection**)connectionData = connection;
    return *connection;
}

///////////////////////////////////

std::string SubProtocol::messageToString(void* messageData, size_t messageLength)
{
    return std::string(static_cast<char*>(messageData), messageLength);
}

///////////////////////////////////

SubProtocol::Result SubProtocol::performStandardProtocol(libwebsocket_context* context, libwebsocket* webSocketInstance, libwebsocket_callback_reasons reason, void* connectionData)
{
    switch(reason)
    {
        case LWS_CALLBACK_ESTABLISHED:
            SubProtocol::getServer(context).handleConnectionOpen(connectionData);
            break;

        case LWS_CALLBACK_CLOSED:
            SubProtocol::getServer(context).handleConnectionClosed(connectionData);
            break;

        case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
            if(SubProtocol::getServer(context).handleConnectionRequest(connectionData, webSocketInstance) != Server::ResponseCode::Success)
                return Result::Fail;
            break;

        case LWS_CALLBACK_RECEIVE:
            SubProtocol::getConnection(connectionData).updateAliveTime();
            return Result::NoAction;

        case LWS_CALLBACK_PROTOCOL_DESTROY:
            {
                unsigned char* derp = new unsigned char[1];
                libwebsocket_write(webSocketInstance, derp, 1, LWS_WRITE_CLOSE);
                return Result::Fail;
            }
        default:
            return Result::NoAction;
    }

    return Result::Success;
}

///////////////////////////////////

bool SubProtocol::getUserCredentials(libwebsocket* webSocketInstance, std::string& username, std::string& password)
{
    lws_token_indexes token = WSI_TOKEN_GET_URI;
    int size = lws_hdr_total_length(webSocketInstance, token);

    if(size <= 1)
        return false;

    char* buffer = new char[size + 1];
    lws_hdr_copy(webSocketInstance, buffer, size + 1, token);

    std::string str(buffer);

    unsigned int slashIndex = str.find('/', 1);
    if(slashIndex == std::string::npos || slashIndex == str.size() - 1)
        return false;

    username = str.substr(1, slashIndex - 1);
    password = str.substr(slashIndex + 1, str.size() - slashIndex - 1);

    return true;
}
