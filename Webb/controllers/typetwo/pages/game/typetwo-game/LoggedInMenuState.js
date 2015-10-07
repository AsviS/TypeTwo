'use strict';

/**
 * \brief Test state
 */
var LoggedInMenuState = function()
{
	function LoggedInMenuState(stateStack, canvas)
	{
		MainMenuState.call(this, stateStack, canvas);
				
		var logoutButton = new GUIButton
		(
			new Rect(0, 0, this._width/3, this._height/10),
			['Log out'],
			function(){stateStack.pop(); config.webSocket.order.disconnect(); stateStack.push(new LoginMenu(stateStack, canvas));}
		);
		
		this._text = new GUIText
		([
			"You are now logged in.",
			"Gz!",
			"",
			"As the surface continually reshaped itself over hundreds of millions of years, continents formed and broke apart. ",
			"They migrated across the surface, occasionally combining to form a supercontinent. Roughly 750 million years ago, ",
			"the earliest-known supercontinent Rodinia, began to break apart. The continents later recombined to form Pannotia, ",
			"600 to 540 million years ago, then finally Pangaea, which broke apart 180 million years ago.",
		]);
		
		var self = this;
		var getUnits = function()
		{
			config.webSocket.fetchData.sendQuery("getUnits", function(response){self._text.setText(response.data);}, function(response){console.log("query timed out");});
		};
		
		var getUnitsButton = new GUIButton
		(
			new Rect(0, 0, this._width/3, this._height/10),
			["Get units"],
			getUnits
		);
		

		this._guiContainer = new GUIContainer([logoutButton, this._text, getUnitsButton], new Rect(0, 0, this._width, this._height));

		getUnitsButton.floatTo('center', 'center');
		logoutButton.setPositionVector(getUnitsButton.getPosition());
		logoutButton.moveY(2 * this._height/10);
		
		this._text.floatTo('center');
		this._text.moveY(this._height / 12);
		
	}
	
	$.extend(LoggedInMenuState.prototype, MainMenuState.prototype,
	{
		_text: null,
		
		update: function(dt)
		{
			this._guiContainer.update(dt);
			
			var messages = config.webSocket.fetchData.getMessages();
			
			for(var i = 0; i < messages.length; i++)
			{
				if(messages[i][0] === "getUnits")
				{
					console.log(messages[i]);
					this._text.setText("yay!");
				}
			}
			
			config.webSocket.fetchData.swapMessagesBuffer();
		},
	});

	return LoggedInMenuState;
}();
