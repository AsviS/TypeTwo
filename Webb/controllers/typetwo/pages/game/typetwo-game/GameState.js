'use strict';

var GameState = function()
{
	function GameState(stateStack, canvas)
	{
		State.call(this, stateStack);
		
		
		var gridWidth = canvas.width / 2;
		var gridHeight = canvas.height * 9 / 10;
		
		var gridBounds = new Rect((canvas.width - gridWidth) / 2, (canvas.height - gridHeight) / 2, gridWidth, gridHeight);
		
		this._gameGrid = new GameGrid(gridBounds, 9);
	}


	$.extend(GameState.prototype, State.prototype,
	{
		_gameGrid: null,
		
		render: function(ct)
		{
			this._gameGrid.render(ct);
		},
		
		update: function(dt)
		{
			this._gameGrid.update(dt);
		},
		
		handleInput: function(dt)
		{
			this._gameGrid.handleInput(dt);
		}
	});

	return GameState;
}();
