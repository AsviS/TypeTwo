'use strict';

/**
 * \brief State that manages the actual gameplay portion of the game.
 * 
 * Contains a State stack within itself, where different rendering 
 * layers are stored, like GameGridState
 * and GameHudState.
 */
var GameState = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param StateStack stateStack
	 * \param Canvas2D canvas
	 */
	function GameState(stateStack, canvas)
	{
		State.call(this, stateStack);
		GameData.init();
		
		this._gameStateStack = new StateStack();
		
		var self = this;
		this._gameStateStack.push(new LoadingState
		(
			self._gameStateStack,
			canvas,
			GameData.isReady,
			function()
			{
				self._gameStateStack.push(new GameGridState(self._gameStateStack, canvas));
				self._gameStateStack.push(new GameHudState(self._gameStateStack, canvas));
			}
		));
	}


	$.extend(GameState.prototype, State.prototype,
	{
		_gameStateStack: null, /**< StateStack "Local" State stack for different rendering layers. */		
		
		/**
		 * \brief Render state
		 * 
		 * \param Canvas.context ct Canvas context to draw state to.
		 * 
		 * \returns True if this state allows states above to be rendered, else false.
		 */
		render: function(ct)
		{
			ct.fillStyle = 'blue';
			ct.fillRect(0, 0, config.canvas.width, config.canvas.height);
			
			this._gameStateStack.render(ct);
			return false;
		},
		
		/**
		 * \brief Update state
		 * 
		 * \param Number dt Time per frame
		 * 
		 * \returns True if this state allows states beneath to be updated, else false.
		 */
		update: function(dt)
		{
			this._gameStateStack.update(dt);
			return false;
		},
		
		/**
		 * \brief Handle device input
		 * 
		 * \param Number dt Time per frame
		 * 
		 * \returns True if this state allows states beneath to handle input, else false.
		 */
		handleInput: function(dt)
		{
			this._gameStateStack.handleInput(dt);
			return false;
		},
	});

	return GameState;
}();
