'use strict';

/**
 * \brief Base class for a WebSocket subprotocol
 */
var WebSocketSubProtocol = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param String name Name of the subprotocol
	 */
	function WebSocketSubProtocol(name)
	{
		this._name = name;
	};
	
	/**
	 * \brief Internal Message object constructor
	 * 
	 * \param Number id ID number of message
	 * \param Object data Data contained in message
	 */
	function Message(id, data)
	{
		this.id = id || 0;
		this.data = data || null;
	}
	
	Message.prototype =
	{
		id: 0, /**< Number ID number message. */
		data: null, /**< Object Data contained in message */
	};

	WebSocketSubProtocol.prototype =
	{
		_name: null, /**< String subprotocol name */
		
		/**
		 * \brief Get subprotocol's name
		 * 
		 * \returns String Subprotocol's name.
		 */
		getName: function()
		{
			return this._name;
		},
		
		/**
		 * \brief Parse a message.
		 * 
		 * First the message is parsed in accordance to the standard subprotocol.
		 * Then it is passed along to the actual subprotocol's _parseInMessage function.
		 * 
		 * \param String message Message to parse
		 * 
		 * \returns Object Parsed message
		 */
		parseInMessage: function(message)
		{
			message = message.trim('\n').split('\n');
			if(message.length <= 0)
				return null;
			
			var id = message.shift();
			return new Message(id, this._parseInMessage(message));
		},
		
		parseOutMessage: function(id, procedure, data)
		{
			data = data || [];
			
			var message = 	id + '\n' + 
							procedure + '\n' + 
							this._parseOutMessage(data);
							
			return message.trim();
		},
		
		/**
		 * \brief Parse message in accordance to this subprotocol
		 * 
		 * This function is meant to be overridden by inheriting subprotocol.
		 * 
		 * \param String message Message to parse
		 * 
		 * \returns Object Parsed message
		 */
		_parseInMessage: function(message)
		{
			return null;
		},
		
		_parseOutMessage: function(message)
		{
			return null;
		}
	};

	return WebSocketSubProtocol;
}();
