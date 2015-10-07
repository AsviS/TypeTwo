'use strict';

/*
 * \brief WebSocket
 */
var Socket = function()
{
	/*
	 * \brief Constructor
	 */
	function Socket(host, port, protocol)
	{
		this.host = host;
		this.port = port;
		this.protocol = protocol;
		this._messagesFrontBuffer = [];
		this._messagesBackBuffer = [];
		this._messagesBuffer1 = [];
		this._messagesBuffer2 = [];
	}
	
	Socket.statusID = 
	{
		UNINITIALIZED: 0,
		CONNECTING: 1,
		OPEN: 2,
		CLOSED: 3,
	};
	
	Socket.prototype =
	{
		websocket: null,
		protocol: 'game-protocol',
		timeout: 5000,
		connected: false,
		queue: [],
		games: [],
		isHost: false,
		id: null,
		username: '',
		password: '',
		status: Socket.statusID.UNINITIALIZED,
		_thisOpenCallbacks: [],
		
		_messagesFrontBuffer: null,
		_messagesBackBuffer: null,
		_messagesBuffer1: null,
		_messagesBuffer2: null,
		
		connect: function(user, success, fail)
		{
			console.log('Connecting to ' + this.host + ':' + this.port);
			this.init(user, success, fail);
		},
		
		
		disconnect: function()
		{
			if(this.websocket) 
			{
				this.websocket.close();
				this.websocket = null;
			}
		},
		
		init: function(username, password, stateStack, canvas)
		{
			if(this.status === Socket.statusID.CONNECTING)
				return;
			
			this.username = username;
			this.password = password;
			this.disconnect();
	
			var url = 'ws://' + this.host + ':' + this.port + "/" + this.username + '/' + this.password;
			this.websocket = new WebSocket(url, this.protocol.getName());
			
			this.status = Socket.statusID.CONNECTING;
			stateStack.push(new ConnectionBarState(stateStack, canvas, 5, this));
						
			var self = this;
			this.websocket.onopen = function()
			{
				self.status = Socket.statusID.OPEN;
				
				for(var i = 0; i < self._thisOpenCallbacks.length; i++)
					self._thisOpenCallbacks[i]();
					
				self._thisOpenCallbacks.length = 0;
			};
	
			
	
			
			this.websocket.onmessage = function(event) 
			{		
				var data = self.protocol.parseMessage(event.data);
				
				if(data)
				{
					if(data.id > 0)
						WebSocketQueryManager.onQueryResponse(data.id, data);
					else
						self._messagesBackBuffer.push(data);	
				}
			};
	
			this.websocket.onclose = function() 
			{
				console.log("Closed!");
				self.status = Socket.statusID.CLOSED;
			};
			
			return true;
		},
		
		send: function(string)
		{
			if(this.status === Socket.statusID.OPEN)
			{
				this.websocket.send("0\n" + string);
				return true;
			}
			else
			{
				console.log('could not send');
				return false;
			}
		},
		
		sendQuery: function(string, success, fail, timeOut)
		{
			if(this.status === Socket.statusID.OPEN)
			{
				var id = WebSocketQueryManager.pushQuery(success, fail, timeOut);
				this.websocket.send(id + "\n" + string);
				return true;
			}
			else
			{
				console.log('could not send');
				return false;
			}
		},
		
		onThisOpen: function(callback)
		{
			this._thisOpenCallbacks.push(callback);
		},
		
		getMessages: function()
		{
			return this._messagesFrontBuffer;
		},
		
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
	};

	return Socket;
}();
