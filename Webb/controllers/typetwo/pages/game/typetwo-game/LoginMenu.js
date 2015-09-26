'use strict';

var LoginMenu = function()
{
	function LoginMenu(stateStack, canvas)
	{
		MainMenuState.call(this, stateStack, canvas);
		
		var width = this._width;
		var height = this._height;
		var buttonSize = new Vector(width/3, height/10);
		var centerX = width/2 - buttonSize.x/2;
		
		var self = this;
		var login = function()
		{
			
			config.webSocket.order.init(username.text, password.text, stateStack, canvas);
			config.webSocket.order.onThisOpen(function(){stateStack.pop(); stateStack.push(new AboutMenuState(stateStack, canvas));});
		};
		
		var username = new GUITextField(new Rect(0, 0, width / 2, height / 10), login);
		var password = new GUITextField(new Rect(0, 0, width / 2, height / 10), login, true);
		
		username.setOriginVector(username.getSize().div(2));
		username.setPosition(width / 2, height / 6);
		
		password.setOriginVector(password.getSize().div(2));
		password.setPosition(width / 2, height / 3);
		
		
		var guiElements = 
		[
			username,
			password,
			new Button
			(
				new Rect(width * 3 / 8, height  / 2, width / 4, height / 10),
				["Log in"], 
				login
			)
		];

		this._guiContainer = new GUIContainer(guiElements, new Rect(0, 0, width, height));
	}
	
	$.extend(LoginMenu.prototype, MainMenuState.prototype);


	return LoginMenu;
}();
