'use strict';

var MainMenu = function()
{
	function MainMenu(stateStack, canvas)
	{
		$.extend(this, new MainMenuState(stateStack, canvas));
		
		var width = canvas.width;
		var height = canvas.height;
		var buttonSize = new Vector(width/3, height/10);
		var centerX = width/2 - buttonSize.x/2;
		var buttons = 
		[
			new Button
			(
				new Vector(centerX - buttonSize.x/1.5, height/2), 
				buttonSize, 
				'Singleplayer', 
				canvas.fontSize, 
				function(){stateStack.pop(); stateStack.push(new GameState(stateStack, canvas));}
			),
			new Button
			(
				new Vector(centerX + buttonSize.x/1.5, height/2), 
				buttonSize, 
				'Multiplayer', 
				canvas.fontSize, 
				function(){stateStack.pop(); stateStack.push(new GameState(stateStack, canvas));}
			),
			new Button
			(
				new Vector(centerX, height*(4/6)),
				buttonSize, 
				'About', 
				canvas.fontSize, 
				function(){stateStack.push(new AboutMenuState(stateStack, canvas));}
			)
		];
		
		this._guiContainer = new GUIContainer(buttons, new Rect());
	}

	return MainMenu;
}();
