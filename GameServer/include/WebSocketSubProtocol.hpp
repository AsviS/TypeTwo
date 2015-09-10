#ifndef TYPETWO_WEBSOCKETSUBPROTOCOL_HPP
#define TYPETWO_WEBSOCKETSUBPROTOCOL_HPP

///////////////////////////////////
// TypeTwo internal headers
class WebSocketServer;
class WebSocketConnection;
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <string>
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
        /// \brief Constructor
        ///
        /// \param name std::string Protocol name
        /// \param sessionDataSize int How much user session data to store
        /// \param callback callback_function* Callback function invoked when receiving message from client
        ///
        ///
        WebSocketSubProtocol(std::string name, int sessionDataSize, callback_function* callback);


        /// \brief Get libwebsocket_protocol representation of this subprotocol
        ///
        /// \return libwebsocket_protocols
        ///
        ///
        libwebsocket_protocols toLibWebSocketProtocol() const;


        /// \brief Get WebSocketServer object stored in LWS context
        ///
        /// \param context libwebsocket_context*
        /// \return WebSocketServer&
        ///
        ///
        static WebSocketServer& getServer(libwebsocket_context* context);

        /// \brief Get WebSocketConnection object stored in connection data.
        ///
        /// \param connectionData void*
        /// \return WebSocketConnection&
        ///
        ///
        static WebSocketConnection& getConnection(void* connectionData);

        /// \brief Create WebSocketConnection object and store it in connectionData
        ///
        /// \param connectionData void*
        /// \param webSocketInstance libwebsocket*
        /// \param server const WebSocketServer&
        /// \return WebSocketConnection&
        ///
        ///
        static WebSocketConnection& createConnection(void* connectionData, libwebsocket* webSocketInstance, const WebSocketServer& server);


        /// \brief Convert message data to STD string
        ///
        /// \param messageData void*
        /// \param messageLength size_t
        /// \return std::string
        ///
        ///
        static std::string messageToString(void* messageData, size_t messageLength);

    protected:
        const std::string         M_NAME;                  ///< Identifying name
        const unsigned int        M_SESSION_DATA_SIZE;     ///< Size of session data. Each connecting client gets data bound to it.
        const callback_function*  M_CALLBACK;              ///< Callback function called when receiving messages from client.
};

#endif // TYPETWO_WEBSOCKETSUBPROTOCOL_HPP
