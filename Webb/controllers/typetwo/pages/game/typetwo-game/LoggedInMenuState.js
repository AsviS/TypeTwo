'use strict';

var LoggedInMenuState = function()
{
	function LoggedInMenuState(stateStack, canvas)
	{
		MainMenuState.call(this, stateStack, canvas);
				
		var logoutButton = new Button
		(
			new Rect(0, 0, this._width/3, this._height/10),
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

		this._guiContainer = new GUIContainer([logoutButton, text], new Rect(0, 0, this._width, this._height));

		logoutButton.floatTo('center', 'center');
		
		text.floatTo('center');
		text.moveY(this._height / 12);
		
	}
	
	$.extend(LoggedInMenuState.prototype, MainMenuState.prototype);

	return LoggedInMenuState;
}();
