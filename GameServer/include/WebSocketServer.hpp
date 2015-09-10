#ifndef TYPETWO_WEBSOCKETSERVER_HPP
#define TYPETWO_WEBSOCKETSERVER_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <map>
///////////////////////////////////


/// \brief WebSocket server
///
/// Creates a WebSocket server that listens to
/// a designated port and responds to designated
/// subprotocols.
class WebSocketServer
{
    public:
        /// \brief Constructor
        ///
        /// \param port unsigned int Port to listen to
        /// \param protocols const std::vector<WebSocketSubProtocol::Ptr>& Protocols to respond to
        ///
        ///
        WebSocketServer(unsigned int port, const std::vector<WebSocketSubProtocol::Ptr>& protocols);

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

        class ClientConnection
        {
            public:
                ClientConnection(std::string username, std::string ip, const WebSocketServer& server) : mUsername(username), mIp(ip), mServer(server){};

                std::string getUsername() const{return mUsername;};
                std::string getIp() const{return mIp;};
                const WebSocketServer& getServer() const{return mServer;};

            private:
                std::string mUsername;
                std::string mIp;
                const WebSocketServer& mServer;

        };

        void addClient(ClientConnection client);
        void removeClient(std::string username);
        const std::map<std::string, ClientConnection>& getClients() const;

        bool userIsConnected(std::string username) const;

    private:
        /// \brief Initialize mProtocols member
        ///
        /// \param protocols const std::vector<WebSocketSubProtocol::Ptr>& Protocols to initialize.
        /// \return void
        ///
        ///  Adds the given protocols to the mProtocols protocol list.
        void initializeProtocols(const std::vector<WebSocketSubProtocol::Ptr>& protocols);



    private:


        libwebsocket_context*   mContext;   ///< WebSocket context
        libwebsocket_protocols* mProtocols; ///< List of protocols to respond to
        std::map<std::string, ClientConnection> mClients; ///< Clients connected to this server.
};



#endif // TYPETWO_WEBSOCKETSERVER_HPP
