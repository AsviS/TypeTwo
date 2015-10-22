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
	function ConnectionBarState(stateStack, canvas, timeOut, socket, onSuccess)
	{
		var self = this;
		this._socket = socket;
		LoadingState.call(this, stateStack, canvas, function(){return self.getProgress();}, onSuccess);
		this._loadingIncrement = 100 / timeOut;
	}
						

	$.extend(ConnectionBarState.prototype, LoadingState.prototype,
	{
		_socket:			null, /**< Socket Socket to connect with. */
		_loadingIncrement: 	0, /**< Number How many percent of the connection bar's max with to increment the current width with per second */
		_progress: 0, /**< Number Percentile progress */
		
		getProgress: function()
		{
			if(this._socket.status === Socket.statusID.OPEN)
			{
				console.log("Connected!");
				return true;
			}
			else if(this._socket.status === Socket.statusID.CLOSED)
			{
				console.log("Cannot connect.");
				return true;
			}
			else
			{
				if(this._progress >= 100)
				{
					console.log("Connection timed out.");
					this._socket.disconnect();
				}
				
				return this._progress;
			}
		},

		/**
		 * \brief Update connection bar
		 * 
		 * \param Number dt Time per frame
		 * \returns Boolean
		 */
		update: function(dt)
		{
			this._progress += dt * this._loadingIncrement;
			
			return LoadingState.prototype.update.call(this, dt);
		},
	});

	return ConnectionBarState;
}();
