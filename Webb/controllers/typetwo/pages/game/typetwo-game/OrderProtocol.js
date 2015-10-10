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
			if(message.length !== 1)
				return false;
			else
				return (message[0] === "1") ? true : false;
		},
	});

	return OrderProtocol;
}();
