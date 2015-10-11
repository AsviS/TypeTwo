'use strict';

/**
 * \brief Main application class
 * 
 * This is the entry point for the game. To start the
 * game, simply declare a TypeTwo object and call its
 * run function.
 */
var TypeTwo = function()
{
	/**
	 * \brief Constructor
	 */
	function TypeTwo()
	{
		config.init();
		this._stateStack = new StateStack();
		
		config.webSocket.order.init("verp", "verp", this._stateStack, config.canvas);
		config.webSocket.fetchData.init("verp", "verp", this._stateStack, config.canvas);
		
		var self = this;
		config.webSocket.order.onOpen(function(){self._stateStack.push(new GameState(self._stateStack, config.canvas));});
		//this._stateStack.push(new LoginMenu(this._stateStack, config.canvas));
		FramerateIndicator.enable();
	}

	TypeTwo.prototype =
	{
		_stateStack:			null, /**< StateStack State stack */
		TIME_PER_FRAME: 		1/60, /**< Number Time to spend on each frame in seconds */
		
		/**
		 * \brief Start the game
		 */
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