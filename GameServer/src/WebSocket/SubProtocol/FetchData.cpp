///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/SubProtocol.hpp"
#include "WebSocket/SubProtocols.hpp"
#include "WebSocket/Server.hpp"
#include "Database/StoredProcedures.hpp"
#include "WebSocket/Connection.hpp"
using namespace WebSocket;
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////

const SubProtocol& SubProtocols::FETCH_DATA = SubProtocol
(
    "fetch-data",
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
        if(result == SubProtocol::Result::Fail)
            return (int)result;
        /////////////////////////////////

        if(reason == LWS_CALLBACK_RECEIVE)
        {
            std::stringstream message(SubProtocol::messageToString(messageData, messageLength));

            std::string id;
            std::string procedure;

            message >> id >> procedure;

            if(procedure == "getUnits")
            {
                Connection& connection = SubProtocol::getConnection(connectionData);

                int userId;
                Database::StoredProcedures::GET_USER_ID.call(connection.getUsername(), userId);
                std::string units = Database::StoredProcedures::GET_UNITS.callAsFetchDataProtocol(userId);
                connection.sendString(id + '\n' + units);
            }
        }

        return 0;
    }
);
