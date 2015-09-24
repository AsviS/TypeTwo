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
		
		var username = new GUITextField(new Rect(50, 50, 250, 50), login);
		var password = new GUITextField(new Rect(50, 120, 250, 50), login, true);
		
		
		
		var guiElements = 
		[
			username,
			password,
			new Button
			(
				new Vector(50, 200), 
				new Vector(150, 50), 
				"Log in", 
				canvas.fontSize,
				login
			)
		];
		
		this._guiContainer = new GUIContainer(guiElements, new Rect());
	}


	return LoginMenu;
}();
