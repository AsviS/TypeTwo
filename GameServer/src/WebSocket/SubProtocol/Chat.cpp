///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/SubProtocol.hpp"
#include "WebSocket/SubProtocols.hpp"
#include "WebSocket/Server.hpp"
#include "WebSocket/Connection.hpp"
using namespace WebSocket;
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


const SubProtocol& SubProtocols::CHAT = SubProtocol
(
    "chat",
    sizeof(Connection*),
    [](libwebsocket_context* context,
                   libwebsocket* webSocketInstance,
                   libwebsocket_callback_reasons reason,
                   void* connectionData,
                   void *messageData,
                   size_t messageLength)
    {
        /////////////////////////////////
        // Always call the standard protocol
        SubProtocol::Result standardProtocolResult = SubProtocol::performStandardProtocol(context, webSocketInstance, reason, connectionData);
        if(standardProtocolResult == SubProtocol::Result::Fail)
           return (int)standardProtocolResult;
        /////////////////////////////////

        switch(reason)
        {
            case LWS_CALLBACK_ESTABLISHED:
            {
                Connection& connection = SubProtocol::getConnection(connectionData);
                connection.getServer().broadcastString
                (
                    "'" + connection.getUsername() + "' connected",
                    connection.getProtocolId()
                );
                break;
            }

            case LWS_CALLBACK_CLOSED:
            {
                Connection& connection = SubProtocol::getConnection(connectionData);
                connection.getServer().broadcastString
                (
                    "'" + connection.getUsername() + "' disconnected",
                    connection.getProtocolId()
                );
                break;
            }

            case LWS_CALLBACK_RECEIVE:
            {
                Connection& connection = SubProtocol::getConnection(connectionData);
                connection.getServer().broadcastString
                (
                    connection.getUsername() + ": " + SubProtocol::messageToString(messageData, messageLength),
                    connection.getProtocolId()
                );
                break;
            }

            default:
                break;
        }

        return 0;
    }
);
