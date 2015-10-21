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
		_parseInMessage: function(message)
		{
			var success = message.length > 0 && message[0] === "1";
			message.shift();
			var data = FetchDataProtocol.prototype.parseDataString(message);
			
			return {success: success, data: data};
		},
		
		_parseOutMessage: function(data)
		{
			return data.join('\n');
		}
	});

	return OrderProtocol;
}();
