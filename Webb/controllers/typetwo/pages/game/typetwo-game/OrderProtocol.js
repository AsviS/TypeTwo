'use strict';

var OrderProtocol = function()
{
	function OrderProtocol()
	{
		WebSocketSubProtocol.call(this, 'order');
	};
	

	$.extend(OrderProtocol.prototype, WebSocketSubProtocol.prototype, 
	{
		_parseMessage: function(message)
		{
			return null;
		},
	});

	return OrderProtocol;
}();
