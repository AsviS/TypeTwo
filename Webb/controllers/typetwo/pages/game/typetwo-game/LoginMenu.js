'use strict';

var LoginMenu = function()
{
	function LoginMenu(stateStack, canvas)
	{
		$.extend(this, new MainMenuState(stateStack, canvas));
		
		var width = canvas.width;
		var height = canvas.height;
		var buttonSize = new Vector(width/3, height/10);
		var centerX = width/2 - buttonSize.x/2;
		
		var login = function()
		{
			
			config.webSocket.order.init(username.text, password.text, stateStack, canvas);
			config.webSocket.order.onThisOpen(function(){stateStack.pop(); stateStack.push(new AboutMenuState(stateStack, canvas));});
		};
		
		var username = new GUITextField(new Rect(width / 4, height / 6, width / 2, height / 10), login);
		var password = new GUITextField(new Rect(width / 4, height / 3, width / 2, height / 10), login, true);
		
		
		
		var guiElements = 
		[
			username,
			password,
			new Button
			(
				new Vector(width * 3 / 8, height  / 2), 
				new Vector(width / 4, height / 10), 
				"Log in", 
				canvas.fontSize,
				login
			)
		];
		
		this._guiContainer = new GUIContainer(guiElements, new Rect());
	}


	return LoginMenu;
}();
