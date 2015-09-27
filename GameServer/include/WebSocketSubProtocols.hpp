#ifndef TYPETWO_WEBSOCKETSUBPROTOCOLS_HPP
#define TYPETWO_WEBSOCKETSUBPROTOCOLS_HPP

///////////////////////////////////
// TypeTwo internal headers
class WebSocketSubProtocol;
///////////////////////////////////


/// \brief Static class containing all available WebSocket subprotocols.
///
class WebSocketSubProtocols
{
    public:
        static const WebSocketSubProtocol& ORDER;       ///< Protocol for ordering items/units/buildings etc.
        static const WebSocketSubProtocol& CHAT;        ///< Chat protocol
        static const WebSocketSubProtocol& FETCH_DATA;  ///< Protocol for fetching data from the game server/database.
};

#endif // TYPETWO_WEBSOCKETSUBPROTOCOLS_HPP

