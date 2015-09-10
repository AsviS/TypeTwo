///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
#include "CompatibilityWrappers.hpp"
#include "WebSocketConnection.hpp"
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
