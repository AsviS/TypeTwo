///////////////////////////////////
// TypeTwo internal headers
#include "WebSocket/Connection.hpp"
#include "WebSocket/Server.hpp"
#include "utility.hpp"
using namespace WebSocket;
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


Connection::Connection(std::string username, libwebsocket* webSocketInstance, const Server& server)
: mServer(server)
, mWebSocketInstance(webSocketInstance)
, mIp(mServer.getIp(mWebSocketInstance))
, mUsername(username)
{
    updateAliveTime();
}

///////////////////////////////////

std::string Connection::getUsername() const
{
    return mUsername;
}

///////////////////////////////////

std::string Connection::getIp() const
{
    return mIp;
}

///////////////////////////////////

const Server& Connection::getServer() const
{
    return mServer;
}

///////////////////////////////////

int Connection::getProtocolId() const
{
    return libwebsockets_get_protocol(mWebSocketInstance)->protocol_index;
}

///////////////////////////////////

std::string Connection::getProtocolName() const
{
    return std::string(libwebsockets_get_protocol(mWebSocketInstance)->name);
}

///////////////////////////////////

void Connection::sendString(std::string str) const
{
    unsigned char* response = (unsigned char*)stringToChar(str);
    libwebsocket_write(mWebSocketInstance, response, str.size(), LWS_WRITE_TEXT);
}

///////////////////////////////////

void Connection::sendLines(std::vector<std::string> lines) const
{
    std::ostringstream stream;
    for(std::string& line : lines)
        stream << line << '\n';

    sendString(stream.str());
}

///////////////////////////////////

void Connection::updateAliveTime()
{
    time(&mLastAliveTime);
}

///////////////////////////////////

time_t Connection::getLastAliveTime() const
{
    return mLastAliveTime;
}

///////////////////////////////////

void Connection::close()
{
    unsigned char* message = new unsigned char();
    libwebsocket_write(mWebSocketInstance, message, 0, LWS_WRITE_CLOSE);
}

///////////////////////////////////

void Connection::silentClose()
{
    libwebsocket_rx_flow_control(mWebSocketInstance, 0);
    close();
}
