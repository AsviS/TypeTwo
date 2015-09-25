///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketConnection.hpp"
#include "WebSocketServer.hpp"
#include "utility.hpp"
///////////////////////////////////

///////////////////////////////////
// STD C++
#include <sstream>
#include <ctime>
///////////////////////////////////

///////////////////////////////////
// libwebsockets
#include "libwebsockets.h"
//////////////////////////////////



WebSocketConnection::WebSocketConnection(std::string username, libwebsocket* webSocketInstance, const WebSocketServer& server)
: mServer(server)
, mWebSocketInstance(webSocketInstance)
, mIp(mServer.getIp(mWebSocketInstance))
, mUsername(username)
{
    updateAliveTime();
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

///////////////////////////////////

void WebSocketConnection::updateAliveTime()
{
    time(&mLastAliveTime);
}

///////////////////////////////////

time_t WebSocketConnection::getLastAliveTime() const
{
    return mLastAliveTime;
}

///////////////////////////////////

void WebSocketConnection::close()
{
    unsigned char* message = new unsigned char();
    libwebsocket_write(mWebSocketInstance, message, 0, LWS_WRITE_CLOSE);
}

///////////////////////////////////

void WebSocketConnection::silentClose()
{
    libwebsocket_rx_flow_control(mWebSocketInstance, 0);
    close();
}
