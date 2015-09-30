///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
#include "WebSocketSubProtocols.hpp"
#include "WebSocketServer.hpp"
#include "UserProvider.hpp"
#include "UnitProvider.hpp"
#include "DatabaseConnections.hpp"
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

        /**
         * STANDARD SUBPROTOCOL:
         *
         *      INCOMING MESSAGES:
         *          Two parts: header and body.
         *          HEADER:
         *              The header contains the message's meta information and consists of the following:
         *                  Line 1: Unsigned integer representing the message's ID. If the ID. The message ID
         *                          is used whenever a message requires a response. In other words, a query. If no response
         *                          is required, the ID is set to 0.
         *                  Line 2: String representing the requested procedure. For example, if the client sends a
         *                          message which contains the string "getUnits" on line 2, the server will handle the data
         *                          in the message's body in accordance to the "getUnits" procedure.
         *
         *          BODY:
         *              The body contains the actual data of the message. How the server interprets the data depends on the
         *              procedure.
         *
         *      OUTGOING MESSAGES:
         *          Same as incoming messages, but with a small modification of the header.
         *          HEADER:
         *              The header contains the message's meta information and consists of the following:
         *                  Line 1: Unsigned integer representing the message's ID. If the ID. The message ID
         *                          is used whenever a message requires a response. In other words, a query. If no response
         *                          is required, the ID is set to 0.
         *
         *          BODY:
         *              The body contains the actual data of the message. The receiver of this outgoing message must now in what context (i.e. procedure)
         *              the message is received in, in order to be able to interpret the data. This is what the message ID is for.
         */

        /**
         * FETCH DATA SUBPROTOCOL:
         *      The fetch data subprotocol expands the standard subprotocol's header for outgoing
         *      messages. The purpose of this protocol is to fetch data from the database.
         *
         *      OUTGOING MESSAGES:
         *          Same as the standard subprotocol's header for outgoing messages, but with an
         *          additional line;
         *              Line 2: String specifying the fetched data's column names. Each column name
         *                      is separated by one whitespace.
         */

        if(reason == LWS_CALLBACK_RECEIVE)
        {
            std::stringstream message(WebSocketSubProtocol::messageToString(messageData, messageLength));

            std::string id;
            std::string procedure;

            message >> id >> procedure;

            if(procedure == "getUnits")
            {
                WebSocketConnection& connection = WebSocketSubProtocol::getConnection(connectionData);

                UnitProvider unitProvider(DatabaseConnections::DEFAULT);
                std::vector<UnitType> unitTypes = unitProvider.getUnitTypes();

                UserProvider userProvider(DatabaseConnections::DEFAULT);

                std::string units = unitProvider.getUnitsAsWebSocketString(userProvider.getId(connection.getUsername()));
                connection.sendString(id + '\n' + units);
            }
        }

        return 0;
    }
);
