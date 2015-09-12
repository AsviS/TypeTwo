///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
#include "WebSocketSubProtocols.hpp"
#include "WebSocketServer.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
#include <sstream>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////


const WebSocketSubProtocol& WebSocketSubProtocols::CHAT = WebSocketSubProtocol
(
    "chat",
    sizeof(WebSocketConnection*),
    [](libwebsocket_context* context,
                   libwebsocket* webSocketInstance,
                   libwebsocket_callback_reasons reason,
                   void* connectionData,
                   void *messageData,
                   size_t messageLength)
    {
        /////////////////////////////////
        // Always call the standard protocol
        WebSocketSubProtocol::performStandardProtocol(context, webSocketInstance, reason, connectionData);
        /////////////////////////////////

        switch(reason)
        {
            case LWS_CALLBACK_ESTABLISHED:
            {
                WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);
                connection.getServer().broadcastString
                (
                    "'" + connection.getUsername() + "' connected"
                );
                break;
            }

            case LWS_CALLBACK_CLOSED:
            {
                WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);
                connection.getServer().broadcastString
                (
                    "'" + connection.getUsername() + "' disconnected"
                );
                break;
            }

            case LWS_CALLBACK_RECEIVE:
            {
                WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);
                connection.getServer().broadcastString
                (
                    connection.getUsername() + ": " + WebSocketSubProtocol::messageToString(messageData, messageLength)
                );
                break;
            }

            default:
                break;
        }

        return 0;
    }
);
