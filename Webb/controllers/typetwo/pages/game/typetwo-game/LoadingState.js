'use strict';

/**
 * \brief Displays a loading screen for things that take tiiiiiiiimeeeee
 */
var LoadingState = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param StateStack stateStack
	 * \param Canvas2D canvas
	 * \param Function getProgress Function that returns either a boolean or a number in the range [0, 100]. 
	 * If the function returns a boolean, it should return true if the loading operation is complete, else false.
	 * If the function returns a number, it should return 100 if the loading operation is complete, else another number
	 * in the range. The number is meant to represent the loading operation's progress in percent.
	 * \param Function onSuccess Callback to invoke when loading is complete. Note that the LoadingState pops itself from
	 * the state stack before calling onSuccess. Default is to do nothing.
	 */
	function LoadingState(stateStack, canvas, getProgress, onSuccess)
	{
		State.call(this, stateStack);
		
		this._getProgress = getProgress;
		this._onSuccess = onSuccess || function(){};
		
		this._guiContainer = new GUIContainer
		(
			[], 
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
		
		var text = new GUIText(["Loading..."]);
		text.setPosition(canvas.width / 4 + 10, canvas.height * 4 / 6);
		text.setColor('white');
		
		this._guiContainer.attachChild(text);
	}
						

	$.extend(LoadingState.prototype, State.prototype,
	{
		_guiContainer:		null, /**< GUIContainer */
		_loadingBar:		null, /**< GUIProgressBar */
		_getProgress: null, /**< Function Get current progress of whatever is loading. */
		_onSuccess: null,	/**< Function Called when loading is complete */

		/**
		 * \brief Update connection bar
		 * 
		 * \param Number dt Time per frame
		 * \returns Boolean
		 */
		update: function(dt)
		{			
			var progress = this._getProgress();

			if(progress === 100 || progress === true)
			{
				this._stateStack.pop();
				this._onSuccess();
			}
			else if(this._loadingBar)
				this._loadingBar.setProgress(progress / 100);

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
