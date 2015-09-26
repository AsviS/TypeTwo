'use strict';

var MainMenu = function()
{
	function MainMenu(stateStack, canvas)
	{
		MainMenuState.call(this, stateStack, canvas);

		var buttonSize = new Vector(this._width/3, this._height/10);
		var centerX = this._width/2 - buttonSize.x/2;
		var buttons = 
		[
			new Button
			(
				new Vector(centerX - buttonSize.x/1.5, this._height/2), 
				buttonSize, 
				'Singleplayer', 
				canvas.fontSize, 
				function(){stateStack.pop(); stateStack.push(new GameState(stateStack, canvas));}
			),
			new Button
			(
				new Vector(centerX + buttonSize.x/1.5, this._height/2), 
				buttonSize, 
				'Multiplayer', 
				canvas.fontSize, 
				function(){stateStack.pop(); stateStack.push(new GameState(stateStack, canvas));}
			),
			new Button
			(
				new Vector(centerX, this._height*(4/6)),
				buttonSize, 
				'About', 
				canvas.fontSize, 
				function(){stateStack.push(new AboutMenuState(stateStack, canvas));}
			)
		];
		
		this._guiContainer = new GUIContainer(buttons, new Rect());
	}
	
	$.extend(MainMenu.prototype, MainMenuState.prototype);

	return MainMenu;
}();
