'use strict';

var TypeTwo = function()
{
	function TypeTwo(canvasId)
	{
		this._canvas = new Canvas2D(canvasId);
		this._stateStack = new StateStack();
		this._stateStack.push(new LoginMenu(this._stateStack, this._canvas));
		//this._stateStack.push(new MainMenu(this._stateStack, this._canvas));
		//this._socket = new Socket("mikael.hernvall.com", 8080, "order", this._stateStack, this._canvas);
	}

	TypeTwo.prototype =
	{
		_canvas: 				null,
		_stateStack:			null,
		TIME_PER_FRAME: 		1/60,
		_socket:				null,
		
		run: function()
		{
			var dt = 0;
			var timeOfLastUpdate = Date.now();
			var timePerFrame = this.TIME_PER_FRAME;
			var stateStack = this._stateStack;
			var canvasContext = this._canvas.context;
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
				}

				stateStack.render(canvasContext);
				requestAnimFrame(gameLoop);
			};
			
			gameLoop();
		},
	};

	
	return TypeTwo;
}();