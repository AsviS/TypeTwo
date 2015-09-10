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

#include "WebSocketServer.hpp"
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
        switch (reason)
        {
            case LWS_CALLBACK_ESTABLISHED:
            {
                WebSocketServer& server = *((WebSocketServer*)libwebsocket_context_user(context));
                WebSocketServer::ClientConnection connection = *(*(WebSocketServer::ClientConnection**)user);
                server.addClient(connection);

                std::cout   << "User '" << connection.getUsername() << "' at " << connection.getIp()
                            << " has connected." << std::endl;

                std::cout << "Logged in users: " << std::endl;
                const std::map<std::string, WebSocketServer::ClientConnection>& clients = server.getClients();
                for(auto client : clients)
                    std::cout << client.second.getUsername() << " -- " << client.second.getIp() << std::endl;

                break;
            }
            case LWS_CALLBACK_CLOSED:
            {
                WebSocketServer& server = *((WebSocketServer*)libwebsocket_context_user(context));
                WebSocketServer::ClientConnection connection = *(*(WebSocketServer::ClientConnection**)user);
                server.removeClient(connection.getUsername());
                std::cout   << "User '" << connection.getUsername() << "' at " << connection.getIp()
                            << " has disconnected." << std::endl;

                 break;
            }
            case LWS_CALLBACK_RECEIVE: {

                const libwebsocket_protocols* protocol = libwebsockets_get_protocol(wsi);

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
            case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
            {
                lws_token_indexes token = WSI_TOKEN_GET_URI;
                int size = lws_hdr_total_length(wsi, token);
                char* c = new char[size + 1];
                lws_hdr_copy(wsi, c, size + 1, token);

                std::string username(c + 1, size - 1);
                std::cout   << "Validating connection from user '" << username << "' at "
                            << getClientIp(context, wsi) << std::endl;

                if(username != "bob" && username != "karl")
                    return -1;

                WebSocketServer& server = *((WebSocketServer*)libwebsocket_context_user(context));

                const std::map<std::string, WebSocketServer::ClientConnection>& clients = server.getClients();
                for(auto client : clients)
                    std::cout << client.second.getUsername() << " -- " << client.second.getIp() << std::endl;

                if(server.userIsConnected(username))
                    return -1;


                token = WSI_TOKEN_KEY;
                size = lws_hdr_total_length(wsi, token);
                std::cout << size << std::endl;
                c = new char[size + 1];
                lws_hdr_copy(wsi, c, size + 1, token);

                std::string authorizationKey(c, size);

                std::cout << "KEY: " << authorizationKey << std::endl;

                *(WebSocketServer::ClientConnection**)user = new WebSocketServer::ClientConnection(username, getClientIp(context, wsi), server);
                break;
            }



/*
WSI_TOKEN_GET_URI,
WSI_TOKEN_POST_URI,
WSI_TOKEN_OPTIONS_URI,
WSI_TOKEN_HOST,
WSI_TOKEN_CONNECTION,
WSI_TOKEN_UPGRADE,
WSI_TOKEN_ORIGIN,
*/

            default:
                break;
        }

        return 0;
    };

    mSessionDataSize = sizeof(WebSocketServer::ClientConnection*);
}
