'use strict';

var AboutMenuState = function()
{
	function AboutMenuState(stateStack, canvas)
	{
		$.extend(this, new MainMenuState(stateStack, canvas));
				
		var width = canvas.width;
		var height = canvas.height;
		var buttonSize = new Vector(width/3, height/10);
		var centerX = width/2 - buttonSize.x/2;
		var guiElements = 
		[
			new Button
			(
				new Vector(centerX, height*(4/6)),
				buttonSize,
				'Log out',
				canvas.fontSize,
				function(){stateStack.pop(); config.webSocket.order.disconnect(); stateStack.push(new LoginMenu(stateStack, canvas));}
			),
			new GUIText
			(
				[
					"You are now logged in.",
					"Gz!",
				],
				new Vector(width/12, height/12),
				width/24
			)
		];
		
		this._guiContainer = new GUIContainer(guiElements, new Rect());
	}

	return AboutMenuState;
}();
