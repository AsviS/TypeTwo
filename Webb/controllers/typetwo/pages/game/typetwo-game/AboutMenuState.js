'use strict';

var AboutMenuState = function()
{
	function AboutMenuState(stateStack, canvas)
	{
		MainMenuState.call(this, stateStack, canvas);
			
		var width = canvas.width;
		var height = canvas.height;		
		var logoutButton = new Button
		(
			new Rect(0, 0, width/3, height/10),
			['Log out'],
			function(){stateStack.pop(); config.webSocket.order.disconnect(); stateStack.push(new LoginMenu(stateStack, canvas));}
		);
		
		var text = new GUIText
		([
			"You are now logged in.",
			"Gz!",
			"",
			"As the surface continually reshaped itself over hundreds of millions of years, continents formed and broke apart. ",
			"They migrated across the surface, occasionally combining to form a supercontinent. Roughly 750 million years ago, ",
			"the earliest-known supercontinent Rodinia, began to break apart. The continents later recombined to form Pannotia, ",
			"600 to 540 million years ago, then finally Pangaea, which broke apart 180 million years ago.",
		]);

		logoutButton.setOrigin(width / 6, height / 20);
		logoutButton.setPosition(width / 2, height * 2 / 3);
		
		text.setPosition(width / 12, height / 12);
		this._guiContainer = new GUIContainer([logoutButton, text], new Rect(0, 0, width, height));
	}
	
	$.extend(AboutMenuState.prototype, MainMenuState.prototype);

	return AboutMenuState;
}();
