#ifndef TYPETWO_WEBSOCKETSERVER_HPP
#define TYPETWO_WEBSOCKETSERVER_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
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
};



#endif // TYPETWO_WEBSOCKETSERVER_HPP
