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
    return *(*(WebSocketConnection**)connectionData);
}

///////////////////////////////////

WebSocketConnection& WebSocketSubProtocol::createConnection(void* connectionData, libwebsocket* webSocketInstance, const WebSocketServer& server)
{
    WebSocketConnection* connection = new WebSocketConnection(webSocketInstance, server);
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
