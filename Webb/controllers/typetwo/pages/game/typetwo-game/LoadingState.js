'use strict';

/**
 * \brief Displays a progress bar during connection attempt
 */
var LoadingState = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param StateStack stateStack
	 * \param Canvas2D canvas
	 * \param Number How long in seconds to try the connection before giving up. 
	 * \param Socket Socket to connect with.
	 */
	function LoadingState(stateStack, canvas, getProgress, onSuccess)
	{
		State.call(this, stateStack);
		
		this._getProgress = getProgress;
		this._onSuccess = onSuccess || function(){};
		
		
		
		var text = new GUIText(["Loading..."]);
		text.setPosition(canvas.width / 4 + 10, canvas.height * 4 / 6);
		text.setColor('white');
		
		
		this._guiContainer = new GUIContainer
		(
			[text], 
			new Rect(0, 0, canvas.width, canvas.height)
		);
		
		if(typeof getProgress() === 'boolean')
		{
			this._loadingBar = null;
		}
		else
		{
			this._loadingBar = new GUIProgressBar(new Rect(canvas.width / 4, canvas.height * 4 / 6, canvas.width / 2, canvas.height / 20));
			this._guiContainer.attachChild(this._loadingBar);
		}			
	}
						

	$.extend(LoadingState.prototype, State.prototype,
	{
		_guiContainer:		null, /**< GUIContainer */
		_loadingBar:		null, /**< GUIProgressBar */
		_getProgress: null, /**< Function Get current progress of whatever is loading. */
		_onSuccess: null,	/**< Function Called when loading is complete */
		_isDone: false,

		/**
		 * \brief Update connection bar
		 * 
		 * \param Number dt Time per frame
		 * \returns Boolean
		 */
		update: function(dt)
		{
			this._stateStack.focus(this);
			
			var progress = this._getProgress();
			
			if((progress === 100 || progress === true) && this._isDone === false)
			{
				this._onSuccess();
				this._isDone = true;
				this._stateStack.pop();
			}
			else if(this._loadingBar)
				this._loadingBar.setProgress(progress);

			return false;
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
			
			return false;
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

	return LoadingState;
}();
