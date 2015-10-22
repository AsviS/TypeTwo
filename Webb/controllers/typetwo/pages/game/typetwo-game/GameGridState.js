'use strict';

var GameGridState = function()
{
	function GameGridState(stateStack, canvas)
	{
		State.call(this, stateStack);
		this._initialize(canvas);
	}


	$.extend(GameGridState.prototype, State.prototype,
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
		},
		
		_initialize: function(canvas)
		{
			var gridWidth = canvas.width / 2;
			var gridBounds = new Rect((canvas.width - gridWidth) / 2, 0, gridWidth, canvas.height);
			
			this._gameGrid = new GameGrid(gridBounds, 3);
		}
	});

	return GameGridState;
}();
