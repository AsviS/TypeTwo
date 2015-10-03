#ifndef TYPETWO_WEBSOCKET_SERVER_HPP
#define TYPETWO_WEBSOCKET_SERVER_HPP

///////////////////////////////////
// TypeTwo internal headers
namespace WebSocket
{
    class SubProtocol;
    class Connection;
}
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <unordered_map>
#include <vector>
#include <list>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
struct libwebsocket_context;
struct libwebsocket_protocols;
struct libwebsocket;
///////////////////////////////////

namespace WebSocket
{
/// \brief WebSocket server
///
/// Creates a WebSocket server that listens to
/// a designated port and responds to designated
/// subprotocols.
class Server
{
    public:
        /// \brief Response codes for connection requests
        ///
        enum class ResponseCode
        {
            Success,                ///< Connection request is OK
            UserAlreadyLoggedIn,    ///< A user of the connection's username is already connected to the server.
            InvalidUserCredentials, ///< The connection passed invalid credentials.
        };

    public:
        /// \brief Constructor
        ///
        /// \param port unsigned int Port to listen to
        /// \param protocols const std::vector<WebSocketSubProtocol::Ptr>& Protocols to respond to
        ///
        ///
        Server(unsigned int port, const std::vector<const SubProtocol*>& protocol);

        /// \brief Destructor
        ///
        ///
        ///
        ~Server();

        /// \brief Start the server.
        ///
        /// \return void
        ///
        ///
        void run();

        /// \brief Get all active client connections of this server of a specific protocol.
        ///
        /// \param protocolId unsigned int ID of protocol.
        /// \return const std::unordered_map<std::string, WebSocketConnection*>&
        ///
        ///
        const std::unordered_map<std::string, Connection*>& getClients(unsigned int protocolId) const;

        /// \brief Handle connection request from client
        ///
        /// \param connectionData void*
        /// \param webSocketInstance libwebsocket*
        /// \return ResponseCode
        ///
        ///
        ResponseCode handleConnectionRequest(void* connectionData, libwebsocket* webSocketInstance);

        /// \brief Handle connection open event from client
        ///
        /// \param connectionData void*
        /// \return void
        ///
        ///
        void handleConnectionOpen(void* connectionData);

        /// \brief Handle connection closed event from client
        ///
        /// \param connectionData void*
        /// \return void
        ///
        ///
        void handleConnectionClosed(void* connectionData);

        /// \brief Get IP adress of connected client.
        ///
        /// \param webSocketInstance libwebsocket* Client connection
        /// \return std::string Client's IP adress
        ///
        ///
        std::string getIp(libwebsocket* webSocketInstance) const;

        /// \brief Toggle verbose flag
        ///
        /// \param flag bool
        /// \return void
        ///
        ///  If true, the server will print detailed information to the console.
        void setVerbose(bool flag);

        /// \brief Broadcast a string to all connections of a specific protocol connected to this server
        ///
        /// \param message std::string Mesage to send
        /// \param protocolId unsigned int ID of protocol to broadcast to.
        /// \param excludeUsers std::list<std::string> Optional parameter. A list of usernames to exclude from the broadcast.
        /// \return void
        ///
        ///
        void broadcastString(std::string message, unsigned int protocolId, std::list<std::string> excludeUsers = std::list<std::string>()) const;

        /// \brief Broadcast lines to all connections connected to this server
        ///
        /// \param lines std::vector<std::string> Lines to send
        /// \param protocolId unsigned int ID of protocol to broadcast to.
        /// \param excludeUsers std::list<std::string> Optional parameter. A list of usernames to exclude from the broadcast.
        /// \return void
        ///
        ///
        void broadcastLines(std::vector<std::string> lines, unsigned int protocolId, std::list<std::string> excludeUsers) const;

    private:
        /// \brief Initialize mProtocols member
        ///
        /// \param protocols const std::vector<WebSocketSubProtocol::Ptr>& Protocols to initialize.
        /// \return libwebsocket_protocols*
        ///
        ///  Adds the given protocols to the mProtocols protocol list.
        libwebsocket_protocols* initializeProtocols(const std::vector<const SubProtocol*>& protocols);

        /// \brief Add a client connection to the server's client map.
        ///
        /// \param client WebSocketConnection
        /// \return void
        ///
        ///
        void addClient(Connection* client);

        /// \brief Remove a client connection from the server's client map.
        ///
        /// \param client WebSocketConnection& Client to remove.
        /// \return void
        ///
        ///
        void removeClient(Connection& client);

        /// \brief Remove a client connection from the server's client map with an iterator.
        ///
        /// \param std::unordered_map<std::string
        /// \param it WebSocketConnection*>::iterator Iterator pointing to the client.
        /// \return void
        ///
        ///
        void removeClient(std::unordered_map<std::string, Connection*>::iterator it);

        /// \brief Validate user credentials.
        ///
        /// \param username std::string
        /// \param password std::string
        /// \return ResponseCode
        ///
        ///
        ResponseCode validateUserCredentials(std::string username, std::string password) const;


        /// \brief Close all connections that are dead.
        ///
        /// \return void
        ///
        ///
        void closeDeadConnections();

    private:
        libwebsocket_context*   mContext;   ///< WebSocket context
        std::vector<std::unordered_map<std::string, Connection*>> mClients; ///< Clients connected to this server. Each index of the vector represents the connection's protocol index.
        bool mVerbose; ///< If true, the server will print detailed information to the console.
};
}


#endif // TYPETWO_WEBSOCKET_SERVER_HPP
