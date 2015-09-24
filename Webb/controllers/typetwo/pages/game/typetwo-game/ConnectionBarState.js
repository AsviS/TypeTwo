'use strict';

var ConnectionBarState = function()
{
	function ConnectionBarState(stateStack, canvas, timeOut, socket)
	{
		this._stateStack = stateStack;
		this._canvas = canvas;
		this._width = canvas.width;
		this._height = canvas.height;
		this._timeOut = timeOut;
		this._socket = socket;
		
		socket.onThisOpen(function()
		{
			console.log("Connected!");
			stateStack.pop();
		});
		
		
		var loadingBarMaxWidth = this._width/2;
		this._loadingBar = 
		{
			left: this._width/2 - loadingBarMaxWidth/2,
			top: this._height*(4/6),
			height: this._height/20,
			width: 0,
			step: loadingBarMaxWidth/this._timeOut,
			maxWidth: loadingBarMaxWidth,
		};
	}
						

	ConnectionBarState.prototype =
	{
		_stateStack:		null,
		_canvas: 			null,
		_width:				0,
		_height:			0,
		_timeOut: 			0,
		_timeElapsed:		0,
		_timeoutCallback:	function(){},
		_loadingBar:		{},
		_socket:			null,

		update: function(dt)
		{								
			if(this._socket.status === Socket.statusID.CLOSED)
			{
				console.log("Cannot connect.");
				
			}
			else if(this._timeElapsed < this._timeOut)
			{
				this._loadingBar.width += dt * this._loadingBar.step;
				this._timeElapsed += dt;
			}
			else
			{
				console.log("Connection timed out.");
				this._socket.disconnect();
				this._stateStack.pop();
			}
			
			return false;
		},
	
		render: function(ct)
		{
			ct.fillStyle = 'black';
			ct.fillRect(0, 0, this._width, this._height);

			ct.fillStyle = 'white';
			ct.textBaseline = "top";
			var text = 'Connecting...';
			ct.fillText(text, this._width/2 - text.length * this._canvas.fontSize/4, this._height/2);

			
			ct.fillStyle = 'orange';
			ct.fillRect(this._loadingBar.left, this._loadingBar.top, this._loadingBar.width, this._loadingBar.height);
			
			
			ct.beginPath();
			ct.rect(this._loadingBar.left, this._loadingBar.top, this._loadingBar.maxWidth, this._loadingBar.height);
			ct.lineWidth = 5;
			ct.strokeStyle = 'gray';
			ct.stroke();	
			
			return false;
		},
		
		handleInput: function(dt)
		{
			return false;
		},
	};

	return ConnectionBarState;
}();
