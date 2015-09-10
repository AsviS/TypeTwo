#ifndef TYPETWO_WEBSOCKETCONNECTION_HPP
#define TYPETWO_WEBSOCKETCONNECTION_HPP

///////////////////////////////////
// TypeTwo internal headers
class WebSocketServer;
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <string>
#include <vector>
///////////////////////////////////


///////////////////////////////////
// libwebsockets
struct libwebsocket;
struct libwebsocket_context;
///////////////////////////////////


/// \brief A WebSocket connection to a client
///
class WebSocketConnection
{
    public:
        /// \brief Constructor
        ///
        /// \param webSocketInstance libwebsocket* LWS instance to bind to.
        /// \param server const WebSocketServer& Server to bind to.
        ///
        ///
        WebSocketConnection(libwebsocket* webSocketInstance, const WebSocketServer& server);

        /// \brief Get connection's username
        ///
        /// \return std::string
        ///
        ///
        std::string getUsername() const;

        /// \brief Get client's IP adress
        ///
        /// \return std::string
        ///
        ///
        std::string getIp() const;

        /// \brief Get the server object this connection is connected to.
        ///
        /// \return const WebSocketServer&
        ///
        ///
        const WebSocketServer& getServer() const;

        /// \brief Send string to client.
        ///
        /// \param str std::string
        /// \return void
        ///
        ///
        void sendString(std::string str) const;

        /// \brief Send strings one line at a time.
        ///
        /// \param lines std::vector<std::string>
        /// \return void
        ///
        ///  The strings are joined with a newline character ('\n') as
        ///  glue.
        void sendLines(std::vector<std::string> lines) const;

    private:
        /// \brief Initialize some member variables.
        ///
        /// \return void
        ///
        ///
        void initialize();

    private:
        const WebSocketServer& mServer; ///< The server this connection is connected to
        libwebsocket* mWebSocketInstance; ///< LWS instance
        std::string mIp; ///< IP adress of client
        std::string mUsername; ///< Username of connection
};

#endif // TYPETWO_WEBSOCKETCONNECTION_HPP

