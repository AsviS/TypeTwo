'use strict';

/**
 * \brief Displays a progress bar during connection attempt
 */
var ConnectionBarState = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param StateStack stateStack
	 * \param Canvas2D canvas
	 * \param Number How long in seconds to try the connection before giving up. 
	 * \param Socket Socket to connect with.
	 */
	function ConnectionBarState(stateStack, canvas, timeOut, socket)
	{
		State.call(this, stateStack);

		this._canvas = canvas;
		this._socket = socket;
		
		socket.onOpen(function()
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
		_canvas: 			null, /**< Canvas2D */
		_socket:			null, /**< Socket Socket to connect with. */
		_guiContainer:		null, /**< GUIContainer */
		_loadingBar:		null, /**< GUIProgressBar */
		_loadingIncrement: 	0, /**< Number How many percent of the connection bar's max with to increment the current width with per second */

		/**
		 * \brief Update connection bar
		 * 
		 * \param Number dt Time per frame
		 * \returns Boolean
		 */
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
	
		/**
		 * \brief Render connection bar
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \returns Boolean
		 */
		render: function(ct)
		{
			ct.fillStyle = 'black';
			ct.fillRect(0, 0, this._width, this._height);
			
			this._guiContainer.render(ct);
			
			return true;
		},
		
		/**
		 * \brief Block other states from handling input.
		 * 
		 * \param Number dt Time per frame.
		 * \returns Boolean
		 */
		handleInput: function(dt)
		{
			return false;
		},
	});

	return ConnectionBarState;
}();
