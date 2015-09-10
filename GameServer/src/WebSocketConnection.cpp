///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketConnection.hpp"
#include "CompatibilityWrappers.hpp"
#include "WebSocketServer.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
//////////////////////////////////



WebSocketConnection::WebSocketConnection(libwebsocket* webSocketInstance, const WebSocketServer& server)
: mServer(server)
, mWebSocketInstance(webSocketInstance)
, mIp(mServer.getIp(mWebSocketInstance))
{
    initialize();
}

///////////////////////////////////

std::string WebSocketConnection::getUsername() const
{
    return mUsername;
}

///////////////////////////////////

std::string WebSocketConnection::getIp() const
{
    return mIp;
}

///////////////////////////////////

const WebSocketServer& WebSocketConnection::getServer() const
{
    return mServer;
}

///////////////////////////////////

void WebSocketConnection::initialize()
{
    lws_token_indexes token = WSI_TOKEN_GET_URI;
    int size = lws_hdr_total_length(mWebSocketInstance, token);
    char* buffer = new char[size + 1];
    lws_hdr_copy(mWebSocketInstance, buffer, size + 1, token);

    mUsername = std::string(buffer + 1, size - 1);
/*
    token = WSI_TOKEN_KEY;
    size = lws_hdr_total_length(mWebSocketInstance, token);

    buffer = new char[size + 1];
    lws_hdr_copy(mWebSocketInstance, buffer, size + 1, token);*/
}

///////////////////////////////////

void WebSocketConnection::sendString(std::string str) const
{
    unsigned char* response = (unsigned char*)stringToChar(str);
    libwebsocket_write(mWebSocketInstance, response, str.size(), LWS_WRITE_TEXT);
}

///////////////////////////////////

void WebSocketConnection::sendLines(std::vector<std::string> lines) const
{
    std::ostringstream stream;
    for(std::string& line : lines)
        stream << line << '\n';

    sendString(stream.str());
}
