'use strict';

/**
 * \brief Test login menu
 */
var LoginMenu = function()
{
	function LoginMenu(stateStack, canvas)
	{
		MainMenuState.call(this, stateStack, canvas);
		
		var login = function()
		{
			config.webSocket.order.init(username.getText(), password.getText(), stateStack, canvas);
			config.webSocket.fetchData.init(username.getText(), password.getText(), stateStack, canvas);
						
			stateStack.push(new ConnectionBarState(stateStack, canvas, 5, config.webSocket.fetchData));
			config.webSocket.fetchData.onOpen(function(){stateStack.pop(); stateStack.push(new GameState(stateStack, canvas));});
		};
		
		var username = new GUITextField(new Rect(0, 0, this._width / 2, this._height / 10), login);
		var password = new GUITextField(username.getBounds(), login, true);
		var loginButton = new GUIButton(new Rect(0, 0, this._width / 4, this._height / 10), ["Log in"], login);
		
		this._guiContainer = new GUIContainer([username, password, loginButton], new Rect(0, 0, this._width, this._height));
		
		
		username.floatTo('center', 'center');
		username.moveY(-username._bounds.height * 3);
		
		password.setPositionVector(username.getPosition());
		password.moveY(password._bounds.height * 1.5);
		
		loginButton.floatTo('center');
		loginButton.setPositionY(password.getPosition().y);
		loginButton.moveY(password._bounds.height * 1.5);
	}
	
	$.extend(LoginMenu.prototype, MainMenuState.prototype);


	return LoginMenu;
}();
