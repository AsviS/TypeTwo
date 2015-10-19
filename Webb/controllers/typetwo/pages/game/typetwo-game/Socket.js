'use strict';

/**
 * \brief WebSocket
 */
var Socket = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param String host Hostname
	 * \param Number port Port number
	 * \param WebSocketSubProtocol protocol Subprotocol to use
	 */
	function Socket(host, port, protocol)
	{
		this._host = host;
		this._port = port;
		this._protocol = protocol;
		
		
		this._messagesFrontBuffer = [];
		this._messagesBackBuffer = [];
		this._messagesBuffer1 = [];
		this._messagesBuffer2 = [];
	
		this._onOpenCallbacks = [];
		
	}
	
	/**
	 * \brief Status codes of connection
	 */
	Socket.statusID = 
	{
		UNINITIALIZED: 0,
		CONNECTING: 1,
		OPEN: 2,
		CLOSED: 3,
	};
	
	Socket.prototype =
	{
		_host: null, /**< String Hostname */
		_port: 0, /**< Number Port number */
		_websocket: null, /**< WebSocket WebSocket connection */
		_protocol: null, /**< WebSocketSubProtocol Connection protocol used */
		_status: Socket.statusID.UNINITIALIZED, /**< Socket.statusID Current connection status */
		_onOpenCallbacks: null, /**< Array Functions to be called when connetion is opened */
		
		_messagesFrontBuffer: null, /**< Array Front buffer of received messages. This buffer is shown to the outside. */
		_messagesBackBuffer: null, /**< Array Back buffer of received messages. This buffer is used to store received messages. */
		_messagesBuffer1: null, /**< Array */
		_messagesBuffer2: null, /**< Array */
		
		/**
		 * \brief Close connection
		 */
		disconnect: function()
		{
			if(this._websocket) 
			{
				this._websocket.close();
				this._websocket = null;
			}
		},
		
		/**
		 * \brief Initialize socket and connect
		 * 
		 * \param String username User name to connect with
		 * \param String password Password to connect with
		 * \param StateStack stateStack State stack to push loading states on
		 * \param Canvas2D canvas Canvas to draw loading states on
		 */
		init: function(username, password, stateStack, canvas)
		{
			if(this._status === Socket.statusID.CONNECTING)
				return;

			this.disconnect();
	
			var url = 'ws://' + this._host + ':' + this._port + "/" + username + '/' + password;
			this._websocket = new WebSocket(url, this._protocol.getName());
			
			this._status = Socket.statusID.CONNECTING;
			
			var self = this;
			this._websocket.onopen = function(){self._onOpen();};
			this._websocket.onmessage = function(message){self._onMessage(message);};
			this._websocket.onclose = function(){self._onClose();};
		},
		
		/**
		 * \brief Send message
		 * 
		 * \param String message Message string to send
		 * 
		 * \returns True if message was sent, else false.
		 */
		send: function(message)
		{
			if(this._status === Socket.statusID.OPEN)
			{
				this._websocket.send("0\n" + message);
				return true;
			}
			else
			{
				console.log('could not send');
				return false;
			}
		},
		
		/**
		 * \brief Send query
		 * 
		 * \param String query Query message to send
		 * \param Function success Function to call when query received a response.
		 * \param Function fail Function to call when query did not receive a response (timed out).
		 * \param Number timeOut Time to wait in milliseconds before dropping the query attempt.
		 * 
		 * \returns True if query was sent, else false.
		 */
		sendQuery: function(query, success, fail, timeOut)
		{
			
			if(this._status === Socket.statusID.OPEN)
			{
				var id = WebSocketQueryManager.pushQuery(success, fail, timeOut);
				this._websocket.send(id + "\n" + query);
				return true;
			}
			else
			{
				console.log('could not send query: ' + query);
				return false;
			}
		},
		
		/**
		 * \brief Add callback on connection open
		 * 
		 * \param Function callback Function to call when connection is opened
		 */
		onOpen: function(callback)
		{
			this._onOpenCallbacks.push(callback);
		},
		
		/**
		 * \brief Get received messages
		 * 
		 * \returns Array Messages received.
		 */
		getMessages: function()
		{
			return this._messagesFrontBuffer;
		},
		
		/**
		 * \brief Swap message buffers
		 * 
		 * This should be done every time before handling all messages.
		 */
		swapMessagesBuffer: function()
		{
			this._messagesFrontBuffer.length = 0;
			
			if(this._messagesFrontBuffer == this._messagesBuffer1)
			{
				this._messagesFrontBuffer = this._messagesBuffer2;
				this._messagesBackBuffer = this._messagesBuffer1;
			}
			else
			{
				this._messagesFrontBuffer = this._messagesBuffer1;
				this._messagesBackBuffer = this._messagesBuffer2;
			}
		},
		
		/**
		 * \brief On connection open event
		 */
		_onOpen: function()
		{
			this._status = Socket.statusID.OPEN;
			for(var i = 0; i < this._onOpenCallbacks.length; i++)
				this._onOpenCallbacks[i]();
				
			this._onOpenCallbacks.length = 0;
		},
		
		/**
		 * \brief On message received event.
		 * 
		 * \param String message Message received
		 */
		_onMessage: function(message) 
		{		
			var data = this._protocol.parseMessage(message.data);
			
			if(data)
			{
				if(data.id > 0)
					WebSocketQueryManager.onQueryResponse(data.id, data);
				else
					this._messagesBackBuffer.push(data);	
			}
		},

		/**
		 * \brief On connection closed event
		 */
		_onClose: function() 
		{
			console.log("Closed!");
			this._status = Socket.statusID.CLOSED;
		},
	};

	return Socket;
}();
