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


/*
 * Data received must be formatted as follows:
 * "itemName\nquantity"
 * where itemName is the name of the item to order, and
 * quantity is how many items to order.
 *
 * For example, to order 9 engineers, send the following
 * string:
 * "engineer\n9"
 */
/// \brief Order data
///
/// Data received must be formatted as follows:
/// "itemName\nquantity"
/// where itemName is the name of the item to order, and
/// quantity is how many items to order.
///
/// For example, to order 9 engineers, send the following
/// string:
/// "engineer\n9"
struct Order
{
    std::string     item;       ///< Item identifier
    unsigned int    quantity;   ///< How many items to order
};

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
            std::string order;
            std::string item;
            int zoneId;

            message >> id >> order >> item >> zoneId;

            Connection& connection = SubProtocol::getConnection(connectionData);

            typedef Database::StoredProcedures SP;
            namespace Stream = Database::Stream::FetchDataProtocol;

            if(order == "unit")
            {
                int userId;
                SP::GET_USER_ID.call(connection.getUsername(), userId);

                std::vector<Database::Row::UnitType> unitTypes = SP::GET_ALL_UNIT_TYPES.call<Database::Row::UnitType>();

                int typeId = 0;
                for(Database::Row::UnitType type : unitTypes)
                    if(type.name == item)
                    {
                        typeId = type.id;
                        break;
                    }

                if(typeId > 0 && zoneId > 0)
                {
                    std::string insertedUnit = Stream::call(SP::INSERT_UNIT, typeId, userId, zoneId, 100);
                    connection.sendString(id + '\n' + "1" + '\n' + insertedUnit);
                }
                else
                    connection.sendString(id + '\n' + "0");
            }

            /*
            std::stringstream message(SubProtocol::messageToString(messageData, messageLength));

            Order order;
            std::getline(message, order.item);
            message >> order.quantity;

            std::ostringstream output;
            output  << "You ordered the following: " << std::endl
                    << "Item: " << order.item << std::endl
                    << "Quantity: " << order.quantity << std::endl;

            SubProtocol::getConnection(connectionData).sendString(output.str());*/
        }

        return 0;
    }
);
