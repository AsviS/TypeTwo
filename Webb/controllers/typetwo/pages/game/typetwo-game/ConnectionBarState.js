'use strict';

var ConnectionBarState = function()
{
	function ConnectionBarState(stateStack, canvas, timeOut, socket)
	{
		State.call(this, stateStack);

		this._canvas = canvas;
		this._socket = socket;
		
		socket.onThisOpen(function()
		{
			console.log("Connected!");
			stateStack.pop();
		});
		
		this._loadingBar = new GUIProgressBar(new Rect(canvas.width / 4, canvas.height * 4 / 6, canvas.width / 2, canvas.height / 20));
		
		var text = new GUIText(["Connecting..."]);
		text.setPosition(canvas.width / 4 + 10, canvas.height * 4 / 6);
		text.setColor('white');
		
		this._guiContainer = new GUIContainer
		(
			[
				this._loadingBar,
				text,
			], 
			new Rect(0, 0, canvas.width, canvas.height)
		);
		this._loadingIncrement = 1 / timeOut;
	}
						

	$.extend(ConnectionBarState.prototype, State.prototype,
	{
		_canvas: 			null,
		_socket:			null,
		_guiContainer:		null,
		_loadingBar:		null,
		_loadingIncrement: 	0,

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
			
			return true;
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
			return false;
		},
	});

	return ConnectionBarState;
}();
