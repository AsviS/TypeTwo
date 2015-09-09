#ifndef TYPETWO_PROTOCOLHELPERFUNCTIONS_HPP
#define TYPETWO_PROTOCOLHELPERFUNCTIONS_HPP

///////////////////////////////////
// STD C++
#include <string>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////


/// \brief Get IP adress of connected client.
///
/// \param context libwebsocket_context* WebSocket context
/// \param wsi libwebsocket* Client connection
/// \return std::string Client's IP adress
///
///
std::string getClientIp(libwebsocket_context* context, libwebsocket* wsi);


#endif // TYPETWO_PROTOCOLHELPERFUNCTIONS_HPP
