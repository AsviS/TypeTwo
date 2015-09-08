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

std::string getClientIp(libwebsocket_context* context, libwebsocket* wsi);


#endif // TYPETWO_PROTOCOLHELPERFUNCTIONS_HPP
