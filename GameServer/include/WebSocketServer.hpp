#ifndef TYPETWO_WEBSOCKETSERVER_HPP
#define TYPETWO_WEBSOCKETSERVER_HPP

///////////////////////////////////
// TypeTwo internal headers
class WebSocketSubProtocol;
class Database;
#include "WebSocketConnection.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <map>
#include <vector>
#include <list>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
struct libwebsocket_context;
struct libwebsocket_protocols;
///////////////////////////////////


/// \brief WebSocket server
///
/// Creates a WebSocket server that listens to
/// a designated port and responds to designated
/// subprotocols.
class WebSocketServer
{
    public:
        /// \brief Response codes for connection requests
        ///
        enum ResponseCode
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
        /// \param db Database& Database object to connect to.
        ///
        ///
        WebSocketServer(unsigned int port, const std::vector<const WebSocketSubProtocol*>& protocol, Database& db);

        /// \brief Destructor
        ///
        ///
        ///
        ~WebSocketServer();

        /// \brief Start the server.
        ///
        /// \return void
        ///
        ///
        void run();

        /// \brief Get all active client connections of this server.
        ///
        /// \return const std::map<std::string, WebSocketConnection*>&
        ///
        ///
        const std::map<std::string, WebSocketConnection*>& getClients() const;

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

        /// \brief Broadcast a string to all connections connected to this server
        ///
        /// \param message std::string Mesage to send
        /// \param excludeUsers std::list<std::string> Optional parameter. A list of usernames to exclude from the broadcast.
        /// \return void
        ///
        ///
        void broadcastString(std::string message, std::list<std::string> excludeUsers = std::list<std::string>()) const;

        /// \brief Broadcast lines to all connections connected to this server
        ///
        /// \param lines std::vector<std::string> Lines to send
        /// \return void
        ///
        ///
        void broadcastLines(std::vector<std::string> lines) const;

    private:
        /// \brief Initialize mProtocols member
        ///
        /// \param protocols const std::vector<WebSocketSubProtocol::Ptr>& Protocols to initialize.
        /// \return void
        ///
        ///  Adds the given protocols to the mProtocols protocol list.
        void initializeProtocols(const std::vector<const WebSocketSubProtocol*>& protocols);

        /// \brief Add a client connection to the server's client map.
        ///
        /// \param client WebSocketConnection
        /// \return void
        ///
        ///
        void addClient(WebSocketConnection* client);

        /// \brief Remove a client connection from the server's client map.
        ///
        /// \param username std::string Username of client connection.
        /// \return void
        ///
        ///
        void removeClient(std::string username);

        /// \brief Remove a client connection from the server's client map with an iterator.
        ///
        /// \param std::map<std::string
        /// \param it WebSocketConnection*>::iterator Iterator pointing to the client.
        /// \return void
        ///
        ///
        void removeClient(std::map<std::string, WebSocketConnection*>::iterator it);

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
        libwebsocket_protocols* mProtocols; ///< List of protocols to respond to
        unsigned int            mNumProtocols; ///< Number of protocols.
        std::map<std::string, WebSocketConnection*> mClients; ///< Clients connected to this server.
        bool mVerbose; ///< If true, the server will print detailed information to the console.
        Database& mDb; ///< Database connection
};



#endif // TYPETWO_WEBSOCKETSERVER_HPP
