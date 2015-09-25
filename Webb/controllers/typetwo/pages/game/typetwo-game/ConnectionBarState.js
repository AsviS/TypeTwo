'use strict';

var ConnectionBarState = function()
{
	function ConnectionBarState(stateStack, canvas, timeOut, socket)
	{
		this._stateStack = stateStack;
		this._canvas = canvas;
		this._bounds = new Rect(canvas.width / 4, canvas.height / 4, canvas.width / 2, canvas.height / 2);
		this._socket = socket;
		
		socket.onThisOpen(function()
		{
			console.log("Connected!");
			stateStack.pop();
		});
		
		this._loadingBar = new GUIProgressBar(new Rect(canvas.width / 4, canvas.height * 4 / 6, canvas.width / 2, canvas.height / 20));
		this._guiContainer = new GUIContainer
		(
			[
				this._loadingBar,
				new GUIText
				(
					["Connecting..."], 
					new Vector(canvas.width / 4 + 10, canvas.height * 4 / 6), 
					new GUIText.FontSettings(undefined, undefined, undefined, 'white', undefined)
				)
			], 
			new Rect(0, 0, canvas.width, canvas.height)
		);
		this._loadingIncrement = 1 / timeOut;
	}
						

	ConnectionBarState.prototype =
	{
		_stateStack:		null,
		_canvas: 			null,
		_guiContainer:		null,
		_bounds:			new Rect(),
		_loadingBar:		{},
		_loadingIncrement: 	0,
		_socket:			null,
		_button:			null,
		_text:				'Connecting...',

		update: function(dt)
		{								
			if(this._socket.status === Socket.statusID.CLOSED)
			{
				console.log("Cannot connect.");
				this._stateStack.pop();
			}
			else if(this._loadingBar.isFinished())
			{
				console.log("Connection timed out.");
				this._socket.disconnect();
				this._stateStack.pop();
			}
			else
			{
				this._loadingBar.increment(dt * this._loadingIncrement);
			}
			
			return false;
		},
	
		render: function(ct)
		{
			ct.fillStyle = 'black';
			ct.fillRect(0, 0, this._width, this._height);
			
			this._guiContainer.render(ct);
			
			return true;
		},
		
		handleInput: function(dt)
		{
			return true;
		},
	};

	return ConnectionBarState;
}();
