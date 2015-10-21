///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/SubProtocol.hpp"
#include "WebSocket/SubProtocols.hpp"
#include "WebSocket/Server.hpp"
#include "WebSocket/Connection.hpp"

#include "Database/StoredProcedures.hpp"
#include "Database/StreamStandard.hpp"
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

void sendResponse(Connection& connection, std::string id, bool success = false, std::string responseData = "")
{
    if(id != "0")
    {
        std::string response = id + '\n' + (success ? "1" : "0");

        if(responseData.size() > 0)
            response += '\n' + responseData;

        connection.sendString(response);
    }
}

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
            namespace Row = Database::Row;

            if(procedure == "unit")
            {
                int userId;
                SP::GET_USER_ID.call(connection.getUsername(), userId);

                int typeId;
                int zoneId;
                message >> typeId >> zoneId;

                std::string insertedUnit = Stream::call(SP::INSERT_UNIT, typeId, userId, zoneId, 100);



                if(insertedUnit.size() > 0)
                    sendResponse(connection, id, true, insertedUnit);
            }
            else if(procedure == "unitMove")
            {
                auto moveStream = Database::Stream::Standard::create(SP::MOVE_UNIT);
                auto getStream = Database::Stream::Standard::create(SP::GET_UNIT_BY_ID);
                std::vector<Row::Unit> result;
                int numMoves = 0;
                bool success = true;
                while(!message.eof())
                {
                    int unitId;
                    int destinationZoneId;

                    message >> unitId;

                    if(!message.eof())
                        message >> destinationZoneId;
                    else
                    {
                        success = false;
                        break;
                    }

                    moveStream.execute(unitId, destinationZoneId);
                    getStream.execute(result, unitId);
                    numMoves++;

                    if(result.size() != numMoves || result.back().zoneId != destinationZoneId)
                    {
                        success = false;
                        break;
                    }
                }

                if(success)
                {
                    sendResponse(connection, id, true);
                    moveStream.commit();
                }
            }


        }

        return 0;
    }
);
