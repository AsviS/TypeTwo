'use strict';
var TypeTwo = function()
{
	function TypeTwo()
	{
		config.init();
		this._stateStack = new StateStack();
		this._stateStack.push(new LoginMenu(this._stateStack, config.canvas));
		FramerateIndicator.enable();
	}

	TypeTwo.prototype =
	{
		_stateStack:			null,
		TIME_PER_FRAME: 		1/60,
		_socket:				null,
		
		run: function()
		{
			var dt = 0;
			var timeOfLastUpdate = Date.now();
			var timePerFrame = this.TIME_PER_FRAME;
			var stateStack = this._stateStack;
			var canvasContext = config.canvas.context;
			var gameLoop = function()
			{
				dt += (Date.now() - timeOfLastUpdate) / 1000;
				timeOfLastUpdate = Date.now();
				while(dt > timePerFrame)
				{
					dt -= timePerFrame;
					
					Input.swapEventBuffers();
					stateStack.handleInput(timePerFrame);
					
					stateStack.update(timePerFrame);
					
					WebSocketQueryManager.update();
				}

				stateStack.render(canvasContext);
				FramerateIndicator.update();
				requestAnimFrame(gameLoop);
			};
			
			gameLoop();
		},
	};

	
	return TypeTwo;
}();