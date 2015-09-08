///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketServer.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <stdexcept>
///////////////////////////////////

WebSocketServer::WebSocketServer(unsigned int port, const std::vector<WebSocketSubProtocol::Ptr>& protocols)
{
    lws_context_creation_info info;
    memset(&info, 0, sizeof info);

    info.port = port;

    initializeProtocols(protocols);
    info.protocols = mProtocols;
    info.extensions = libwebsocket_get_internal_extensions();
    info.gid = -1;
    info.uid = -1;

    mContext = libwebsocket_create_context(&info);

    if (!mContext)
        throw std::runtime_error("Could not initialize WebSocket server.");
}

///////////////////////////////////

void WebSocketServer::initializeProtocols(const std::vector<WebSocketSubProtocol::Ptr>& protocols)
{

    unsigned int size = protocols.size() + 2;
    mProtocols = new libwebsocket_protocols[size];

    mProtocols[0] =
    {
        "http-only",
        [](libwebsocket_context * context, libwebsocket *wsi, libwebsocket_callback_reasons reason, void *user, void *in, size_t len){return 0;},
        0
    };

    for(unsigned int i = 1; i < size - 1; i++)
        mProtocols[i] = protocols[i - 1]->toLibWebSocketProtocol();

    mProtocols[size - 1] = {nullptr, nullptr, 0};
};

///////////////////////////////////

WebSocketServer::~WebSocketServer()
{
    libwebsocket_context_destroy(mContext);
    delete[] mProtocols;
}

///////////////////////////////////

void WebSocketServer::run()
{
    while(true)
        libwebsocket_service(mContext, 50);
}
