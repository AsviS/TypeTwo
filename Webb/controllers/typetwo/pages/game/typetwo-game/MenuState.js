'use strict';
var MenuState = function()
{
	function MenuState()
	{
	}

	$.extend(MenuState.prototype, State.prototype,
	{
		_guiContainer: new GUIContainer(),
		
		render: function(ct)
		{
			this._guiContainer.render(ct);
		},
				
		update: function(dt)
		{
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