///////////////////////////////////
// TypeTwo internal headers
#include "ProtocolHelperFunctions.hpp"
///////////////////////////////////

std::string getClientIp(libwebsocket_context* context, libwebsocket* wsi)
{
    unsigned int BUFFER_SIZE = 50;
    char ip[BUFFER_SIZE];
    memset(&ip, 0, BUFFER_SIZE);

    libwebsockets_get_peer_addresses(context, wsi, libwebsocket_get_socket_fd(wsi), ip, 0, ip, BUFFER_SIZE);

    return std::string(ip);
}
