'use strict';

var WebSocketSubProtocol = function()
{
	function WebSocketSubProtocol(name)
	{
		this._name = name;
	};
	
	function Message(id, data)
	{
		this.id = id;
		this.data = data || null;
	}

	WebSocketSubProtocol.prototype =
	{
		_name: null,
		
		getName: function()
		{
			return this._name;
		},
		
		parseMessage: function(message)
		{
			message = message.trim('\n').split('\n');
			if(message.length <= 0)
				return null;
			
			var id = message.shift();
			return new Message(id, this._parseMessage(message));
		},
		
		_parseMessage: function(message)
		{
			return null;
		},
	};

	return WebSocketSubProtocol;
}();
