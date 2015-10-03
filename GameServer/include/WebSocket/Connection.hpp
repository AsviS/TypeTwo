#ifndef TYPETWO_WEBSOCKET_CONNECTION_HPP
#define TYPETWO_WEBSOCKET_CONNECTION_HPP

///////////////////////////////////
// TypeTwo internal headers
namespace WebSocket
{
    class Server;
}
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

namespace WebSocket
{
/// \brief A WebSocket connection to a client
///
class Connection
{
    public:
        /// \brief Constructor
        ///
        /// \param username std::string Connection's username.
        /// \param webSocketInstance libwebsocket* LWS instance to bind to.
        /// \param server const WebSocketServer& Server to bind to.
        ///
        ///
        Connection(std::string username, libwebsocket* webSocketInstance, const Server& server);

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
        const Server& getServer() const;


        /// \brief Get this connection's protocol's ID
        ///
        /// \return int Protocol ID of this connection.
        ///
        ///
        int getProtocolId() const;


        /// \brief Get this connection's protocol's name
        ///
        /// \return std::string Protocol name of this connection.
        ///
        ///
        std::string getProtocolName() const;

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

        /// \brief Update the time the connection showed a sign of being alive.
        ///
        /// \return void
        ///
        ///
        void updateAliveTime();


        /// \brief Get the time the connection showed a sign of being alive.
        ///
        /// \return time_t Last time connection showed a sign of being alive.
        ///
        ///
        time_t getLastAliveTime() const;


        /// \brief Close connection to client
        ///
        /// \return void
        ///
        ///
        void close();


        /// \brief Close connection to client silently, without triggering any protocols server-side.
        ///
        /// \return void
        ///
        ///
        void silentClose();

    private:
        const Server& mServer; ///< The server this connection is connected to
        libwebsocket* mWebSocketInstance; ///< LWS instance
        std::string mIp; ///< IP adress of client
        std::string mUsername; ///< Username of connection
        time_t  mLastAliveTime; ///< Last time connection showed a sign of being alive.
};
}

#endif // TYPETWO_WEBSOCKET_CONNECTION_HPP

