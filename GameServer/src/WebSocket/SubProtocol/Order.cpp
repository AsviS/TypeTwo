///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/SubProtocol.hpp"
#include "WebSocket/SubProtocols.hpp"
#include "WebSocket/Server.hpp"
#include "WebSocket/Connection.hpp"

#include "Database/StoredProcedures.hpp"
#include "Database/StreamFetchDataProtocol.hpp"
#include "Database/Row.hpp"
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


const SubProtocol& SubProtocols::ORDER = SubProtocol
(
    "order",
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
        SubProtocol::Result result = SubProtocol::performStandardProtocol(context, webSocketInstance, reason, connectionData);
        if(result != SubProtocol::Result::NoAction)
            return (int)result;
        /////////////////////////////////



        if(reason == LWS_CALLBACK_RECEIVE)
        {

            std::stringstream message(SubProtocol::messageToString(messageData, messageLength));

            std::string id;
            std::string procedure;

            message >> id >> procedure;

            Connection& connection = SubProtocol::getConnection(connectionData);

            typedef Database::StoredProcedures SP;
            namespace Stream = Database::Stream::FetchDataProtocol;

            bool success = false;
            std::string responseData;
            if(procedure == "unit")
            {
                int userId;
                SP::GET_USER_ID.call(connection.getUsername(), userId);

                int typeId;
                int zoneId;
                message >> typeId >> zoneId;

                std::string insertedUnit = Stream::call(SP::INSERT_UNIT, typeId, userId, zoneId, 100);

                if(insertedUnit.size() > 0)
                {
                    success = true;
                    responseData = insertedUnit;
                }
            }

            if(id != "0")
            {
                std::string response = id + '\n' + (success ? "1" : "0");

                if(responseData.size() > 0)
                    response += '\n' + responseData;

                connection.sendString(response);
            }
        }

        return 0;
    }
);
