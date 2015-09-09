///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocols.hpp"
#include "ProtocolHelperFunctions.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <iostream>
#include <sstream>
//#include <cstring>
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

OrderProtocol::OrderProtocol()
{
    mName = "order";
    mCallback = [](libwebsocket_context *context,
                   libwebsocket *wsi,
                   libwebsocket_callback_reasons reason,
                   void *user,
                   void *in,
                   size_t len)
    {
        switch (reason) {
            case LWS_CALLBACK_ESTABLISHED:
                std::cout << getClientIp(context, wsi);
                std::cout << "Order connection established" << std::endl;
                break;
            case LWS_CALLBACK_RECEIVE: {

                // Incoming message.
                std::string message;
                message.assign(static_cast<char*>(in), len);
                std::stringstream stream(message);

                Order order;
                std::getline(stream, order.item);
                stream >> order.quantity;

                std::ostringstream outputStream;
                outputStream    << "You ordered the following: " << std::endl
                                << "Item: " << order.item << std::endl
                                << "Quantity: " << order.quantity << std::endl;

                std::string output = outputStream.str();
				unsigned char* response = stringToUChar(output);
                libwebsocket_write(wsi, response, output.size(), LWS_WRITE_TEXT);
                break;
            }
            default:
                break;
        }

        return 0;
    };
}
