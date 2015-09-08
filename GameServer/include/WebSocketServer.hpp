#ifndef TYPETWO_WEBSOCKETSERVER_HPP
#define TYPETWO_WEBSOCKETSERVER_HPP

///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
///////////////////////////////////

class WebSocketServer
{
    public:
        WebSocketServer(unsigned int port, const std::vector<WebSocketSubProtocol::Ptr>& protocols);
        ~WebSocketServer();

        void run();

    private:
        void initializeProtocols(const std::vector<WebSocketSubProtocol::Ptr>& protocols);


    private:
        libwebsocket_context*   mContext;
        libwebsocket_protocols* mProtocols;
};



#endif // TYPETWO_WEBSOCKETSERVER_HPP
