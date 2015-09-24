'use strict';
var Socket = function()
{
	function Socket(host, port, protocol)
	{
		this.host = host;
		this.port = port;
		this.protocol = protocol;
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
			this.username = username;
			this.password = password;
			this.disconnect();
	
			var url = 'ws://' + this.host + ':' + this.port + "/" + this.username + '/' + this.password;
			this.websocket = new WebSocket(url, this.protocol);
			
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
				console.log("Received message: " + event.data);
			};
	
			this.websocket.onclose = function() 
			{
				console.log("Closed!");
				self.status = Socket.statusID.CLOSED;
			};
			
			return true;
		},
		
		send: function(obj)
		{
			if(this.status === Socket.statusID.OPEN)
			{
				this.websocket.send(JSON.stringify(obj));
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
		}
	};

	return Socket;
}();
