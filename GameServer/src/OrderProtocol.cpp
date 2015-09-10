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

const WebSocketSubProtocol& WebSocketSubProtocols::ORDER_PROTOCOL = WebSocketSubProtocol
(
    "order",
    sizeof(WebSocketConnection*),
    [](libwebsocket_context* context,
                   libwebsocket* webSocketInstance,
                   libwebsocket_callback_reasons reason,
                   void* connectionData,
                   void *messageData,
                   size_t messageLength)
    {
        switch (reason)
        {
            case LWS_CALLBACK_ESTABLISHED:
                WebSocketSubProtocol::getServer(context).handleConnectionOpen(connectionData);
                break;

            case LWS_CALLBACK_CLOSED:
                WebSocketSubProtocol::getServer(context).handleConnectionClosed(connectionData);
                break;

            case LWS_CALLBACK_RECEIVE:
            {
                std::stringstream message(WebSocketSubProtocol::messageToString(messageData, messageLength));

                Order order;
                std::getline(message, order.item);
                message >> order.quantity;

                std::ostringstream output;
                output  << "You ordered the following: " << std::endl
                        << "Item: " << order.item << std::endl
                        << "Quantity: " << order.quantity << std::endl;

                WebSocketSubProtocol::getConnection(connectionData).sendString(output.str());

                WebSocketSubProtocol::getConnection(connectionData).sendLines(
                {
                    "It",
                    "is",
                    "very",
                    "easy",
                    "to",
                    "send",
                    "many",
                    "lines",
                    ":)"
                });
                break;
            }

            case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
                return (int)WebSocketSubProtocol::getServer(context).handleConnectionRequest(connectionData, webSocketInstance);

            default:
                break;
        }

        return 0;
    }
);
