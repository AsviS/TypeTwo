///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
#include "WebSocketSubProtocols.hpp"
#include "WebSocketServer.hpp"
#include "DatabaseStoredProcedures.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////

const WebSocketSubProtocol& WebSocketSubProtocols::FETCH_DATA = WebSocketSubProtocol
(
    "fetch-data",
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
        WebSocketSubProtocol::Result result = WebSocketSubProtocol::performStandardProtocol(context, webSocketInstance, reason, connectionData);
        if(result == WebSocketSubProtocol::Result::Fail)
            return (int)result;
        /////////////////////////////////

        if(reason == LWS_CALLBACK_RECEIVE)
        {
            std::stringstream message(WebSocketSubProtocol::messageToString(messageData, messageLength));

            std::string id;
            std::string procedure;

            message >> id >> procedure;

            if(procedure == "getUnits")
            {
                WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);

                int userId;
                DatabaseStoredProcedures::GET_USER_ID.call(connection.getUsername(), userId);
                std::string units = DatabaseStoredProcedures::GET_UNITS.callAsFetchDataProtocol(userId);
                connection.sendString(id + '\n' + units);
            }
        }

        return 0;
    }
);
