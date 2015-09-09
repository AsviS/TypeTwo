///////////////////////////////////
// TypeTwo internal headers
#include "WebSocketSubProtocol.hpp"
#include "ProtocolHelperFunctions.hpp"
///////////////////////////////////

std::vector<WebSocketSubProtocol::Ptr> WebSocketSubProtocol::factory(std::vector<WebSocketSubProtocol*> protocols)
{
    std::vector<Ptr> result;
    result.resize(protocols.size());
    for(unsigned int i = 0; i < protocols.size(); i++)
       result[i] = std::unique_ptr<WebSocketSubProtocol>(protocols[i]);

    return result;
}

///////////////////////////////////

libwebsocket_protocols WebSocketSubProtocol::toLibWebSocketProtocol() const
{
    return {stringToChar(mName), mCallback, mSessionDataSize};
}
