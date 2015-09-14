///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
#include "CompatibilityWrappers.hpp"
#include "WebSocketConnection.hpp"
#include "WebSocketServer.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
#include <stdexcept>
///////////////////////////////////


WebSocketSubProtocol::WebSocketSubProtocol(std::string name, int sessionDataSize, callback_function* callback)
: M_NAME(name)
, M_SESSION_DATA_SIZE(sessionDataSize)
, M_CALLBACK(callback)
{
}

///////////////////////////////////

libwebsocket_protocols WebSocketSubProtocol::toLibWebSocketProtocol() const
{
    return
    {
        stringToChar(M_NAME),
        M_CALLBACK,
        M_SESSION_DATA_SIZE
    };
}

///////////////////////////////////

WebSocketServer& WebSocketSubProtocol::getServer(libwebsocket_context* context)
{
    return *((WebSocketServer*)libwebsocket_context_user(context));
}

///////////////////////////////////

WebSocketConnection& WebSocketSubProtocol::getConnection(void* connectionData)
{
    WebSocketConnection* connection = (*(WebSocketConnection**)connectionData);

    if(connection == nullptr)
        throw std::runtime_error("DEVELOPMENT ERROR: \nA connection has been established without having its connection data initialized. This may be caused by an invalid protocol that does not use the standard protocol properly. See existing protocols for examples. \n");

    return *(*(WebSocketConnection**)connectionData);
}

///////////////////////////////////

WebSocketConnection& WebSocketSubProtocol::createConnection(std::string username, void* connectionData, libwebsocket* webSocketInstance, const WebSocketServer& server)
{
    WebSocketConnection* connection = new WebSocketConnection(username, webSocketInstance, server);
    *(WebSocketConnection**)connectionData = connection;
    return *connection;
}

///////////////////////////////////

std::string WebSocketSubProtocol::messageToString(void* messageData, size_t messageLength)
{
    return std::string(static_cast<char*>(messageData), messageLength);
}

///////////////////////////////////

WebSocketSubProtocol::Result WebSocketSubProtocol::performStandardProtocol(libwebsocket_context* context, libwebsocket* webSocketInstance, libwebsocket_callback_reasons reason, void* connectionData)
{
    switch(reason)
    {
        case LWS_CALLBACK_ESTABLISHED:
            WebSocketSubProtocol::getServer(context).handleConnectionOpen(connectionData);
            break;

        case LWS_CALLBACK_CLOSED:
            WebSocketSubProtocol::getServer(context).handleConnectionClosed(connectionData);
            break;

        case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
            if(WebSocketSubProtocol::getServer(context).handleConnectionRequest(connectionData, webSocketInstance) != WebSocketServer::ResponseCode::Success)
                return Result::Fail;
            break;
        default:
            return Result::NoAction;
    }

    return Result::Success;
}

///////////////////////////////////

bool WebSocketSubProtocol::getUserCredentials(libwebsocket* webSocketInstance, std::string& username, std::string& password)
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
