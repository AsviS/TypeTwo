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
        /// \brief Tri-state boolean for standard protocol result
        ///
        enum Result
        {
            Success,    ///< Request was processed and valid
            Fail,       ///< Request was processed and invalid
            NoAction    ///< Request was not processed
        };


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
        /// \param username std::string
        /// \param connectionData void*
        /// \param webSocketInstance libwebsocket*
        /// \param server const WebSocketServer&
        /// \return WebSocketConnection&
        ///
        ///
        static WebSocketConnection& createConnection(std::string username, void* connectionData, libwebsocket* webSocketInstance, const WebSocketServer& server);


        /// \brief Convert message data to STD string
        ///
        /// \param messageData void*
        /// \param messageLength size_t
        /// \return std::string
        ///
        ///
        static std::string messageToString(void* messageData, size_t messageLength);

        /// \brief Perform the standard protocol
        ///
        /// \param context libwebsocket_context*
        /// \param webSocketInstance libwebsocket*
        /// \param reason libwebsocket_callback_reasons
        /// \param connectionData void*
        /// \return Result Result of the standard protocol processing the request. See the Result definition for more info.
        ///
        /// The standard protocol takes care of opening and closing connections. It
        /// should usually be called at the start of a protocol's callback function.
        /// See existing protocols for examples.
        static Result performStandardProtocol(libwebsocket_context* context, libwebsocket* webSocketInstance, libwebsocket_callback_reasons reason, void* connectionData);


        static bool getUserCredentials(libwebsocket* webSocketInstance, std::string& username, std::string& password);


    protected:
        const std::string         M_NAME;                  ///< Identifying name
        const unsigned int        M_SESSION_DATA_SIZE;     ///< Size of session data. Each connecting client gets data bound to it.
        const callback_function*  M_CALLBACK;              ///< Callback function called when receiving messages from client.
};

#endif // TYPETWO_WEBSOCKETSUBPROTOCOL_HPP
