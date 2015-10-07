'use strict';

/**
 * \brief WebSocket subprotocol for making orders (buying buildings, moving units etc.)
 */
var OrderProtocol = function()
{
	/**
	 * \brief Constructor
	 */
	function OrderProtocol()
	{
		WebSocketSubProtocol.call(this, 'order');
	};
	

	$.extend(OrderProtocol.prototype, WebSocketSubProtocol.prototype, 
	{
		/**
		 * \brief Parse a message into conformity with the order subprotocol.
		 * 
		 * \param String message Message to parse
		 */
		_parseMessage: function(message)
		{
			return null;
		},
	});

	return OrderProtocol;
}();
