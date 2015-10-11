///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/SubProtocol.hpp"
#include "WebSocket/SubProtocols.hpp"
#include "WebSocket/Server.hpp"
#include "Database/StoredProcedures.hpp"
#include "WebSocket/Connection.hpp"
#include "Database/FetchDataProtocolStream.hpp"
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

            Connection& connection = SubProtocol::getConnection(connectionData);

            typedef Database::StoredProcedures SP;
            using namespace Database;


            if(procedure == "getUnitsByZoneId")
            {
                int zoneId;
                message >> zoneId;
                std::string units = FetchDataProtocol::call(SP::GET_UNITS_BY_ZONE_ID, zoneId);
                connection.sendString(id + '\n' + units);
            }
            else if(procedure == "getUnits")
            {
                int userId;
                Database::StoredProcedures::GET_USER_ID.call(connection.getUsername(), userId);
                std::string units = FetchDataProtocol::call(SP::GET_UNITS, userId);
                connection.sendString(id + '\n' + units);
            }
            else if(procedure == "getUnitTypes")
            {
                connection.sendString(id + '\n' + FetchDataProtocol::call(SP::GET_ALL_UNIT_TYPES));
            }
            else if(procedure == "getVisibleUnits")
            {
                int userId;
                Database::StoredProcedures::GET_USER_ID.call(connection.getUsername(), userId);

                std::vector<int> zoneIds = Database::StoredProcedures::GET_USER_ZONE_IDS.call<int>(userId);

                auto stream = Database::FetchDataProtocol::createStream(Database::StoredProcedures::GET_UNITS_BY_ZONE_ID);
                for(int zoneId : zoneIds)
                    stream.execute(zoneId);

                connection.sendString(id + '\n' + stream.fetch());
            }
        }

        return 0;
    }
);
