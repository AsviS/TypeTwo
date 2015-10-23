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
		 * \brief Parse an incoming message into conformity with the order subprotocol.
		 * 
		 * \param String message Message to parse
		 * 
		 * \returns Object OrderProtocol format. Contains boolean "success" indicating whether the
		 * was accepted and an array of objects "data" containing the server's response.
		 */
		_parseInMessage: function(message)
		{
			var success = message.length > 0 && message[0] === "1";
			message.shift();
			var data = FetchDataProtocol.prototype.parseDataString(message);
			
			return {success: success, data: data};
		},
		
		/**
		 * \brief Parse outgoing message into conformity with the order subprotocol
		 * 
		 * \param Array Array of strings to parse.
		 * 
		 * \returns String Parsed message.
		 */
		_parseOutMessage: function(data)
		{
			return data.join('\n');
		}
	});

	return OrderProtocol;
}();
