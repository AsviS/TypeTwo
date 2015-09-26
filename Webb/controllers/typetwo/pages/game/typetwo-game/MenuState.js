'use strict';
var MenuState = function()
{
	function MenuState(stateStack)
	{
		State.call(this, stateStack);
		
		this._guiContainer = new GUIContainer();
	}

	$.extend(MenuState.prototype, State.prototype,
	{
		render: function(ct)
		{
			this._guiContainer.render(ct);
		},
				
		update: function(dt)
		{
			this._guiContainer.update(dt);
			return false;
		},
		
		handleInput: function(dt)
		{
			this._guiContainer.handleInput(dt);
			return false;
		},
	});
	
	return MenuState;
}();