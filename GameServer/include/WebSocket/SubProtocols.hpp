#ifndef TYPETWO_WEBSOCKET_SUBPROTOCOLS_HPP
#define TYPETWO_WEBSOCKET_SUBPROTOCOLS_HPP

///////////////////////////////////
// TypeTwo internal headers
namespace WebSocket
{
    class SubProtocol;
}
///////////////////////////////////

namespace WebSocket
{
/// \brief Static class containing all available WebSocket subprotocols.
///
class SubProtocols
{
    public:
        /// \brief Order handling
        ///
        /// Receives orders from client and returns a response
        /// indicating whether that order was successful or not.
        ///
        /// An order can be, for example, ordering the construction
        /// of units and buildings or order a unit to move.
        ///
        static const SubProtocol& ORDER;

        /// \brief Chat
        ///
        /// Receives messages from clients and broadcasts
        /// them to all other connected clients.
        ///
        static const SubProtocol& CHAT;

        /// \brief Data fetching
        ///
        /// Receives data requests from the client and relays
        /// the requested data to the client from the database.
        ///
        static const SubProtocol& FETCH_DATA;
};
}

#endif // TYPETWO_WEBSOCKET_SUBPROTOCOLS_HPP

