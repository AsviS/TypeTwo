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

/// \brief Base class for a WebSocket subprotocol
///
/// A WebSocket subprotocol can be explained as a
/// connection type. A connection is bound to one
/// subprotocol only during its entire lifetime.
class WebSocketSubProtocol
{
    public:
        typedef std::unique_ptr<WebSocketSubProtocol> Ptr;

        /// \brief Generate unique pointers from WebSocketSubProtocol object pointers
        ///
        /// \param protocols std::vector<WebSocketSubProtocol*>
        /// \return std::vector<Ptr> Input pointers stored as unique pointers.
        ///
        ///
        static std::vector<Ptr> factory(std::vector<WebSocketSubProtocol*> protocols);

        /// \brief Get libwebsocket_protocol representation of this subprotocol
        ///
        /// \return virtual libwebsocket_protocols
        ///
        ///
        virtual libwebsocket_protocols toLibWebSocketProtocol() const;

    protected:
        std::string         mName;              ///< Identifying name
        callback_function*  mCallback;          ///< Callback function called when receiving messages from Client.
        unsigned int        mSessionDataSize;   ///< Size of session data.
};

#endif // TYPETWO_WEBSOCKETSUBPROTOCOL_HPP
