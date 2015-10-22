'use strict';

var GameState = function()
{
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
		_gameStateStack: null,
		
		
		render: function(ct)
		{
			ct.fillStyle = 'blue';
			ct.fillRect(0, 0, config.canvas.width, config.canvas.height);
			
			this._gameStateStack.render(ct);
		},
		
		update: function(dt)
		{
			this._gameStateStack.update(dt);
		},
		
		handleInput: function(dt)
		{
			this._gameStateStack.handleInput(dt);
		},
	});

	return GameState;
}();
