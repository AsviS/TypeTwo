#ifndef TYPETWO_WEBSOCKETSUBPROTOCOL_HPP
#define TYPETWO_WEBSOCKETSUBPROTOCOL_HPP

///////////////////////////////////
// STD C++
#include <string>
#include <memory>
#include <vector>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
///////////////////////////////////

class WebSocketSubProtocol
{
    public:
        typedef std::unique_ptr<WebSocketSubProtocol> Ptr;

        static std::vector<Ptr> factory(std::vector<WebSocketSubProtocol*> protocols);

        virtual libwebsocket_protocols toLibWebSocketProtocol() const;

    protected:
        std::string         mName;
        callback_function*  mCallback;
        unsigned int        mSessionDataSize;
};

#endif // TYPETWO_WEBSOCKETSUBPROTOCOL_HPP
