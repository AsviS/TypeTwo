'use strict';
var State = function()
{
	function State(stateStack)
	{
		this._stateStack = stateStack;
	}


	State.prototype =
	{
		_stateStack: null,
		
		update: function(dt)
		{
		},
	
		render: function(ct)
		{
		},
		
		handleInput: function(dt)
		{
		},
	};



	return State;
}();
