'use strict';
var StateStack = function()
{
	function StateStack()
	{

	}


	StateStack.prototype =
	{
		_stateStack: [],
		_eventQueue: [],
		_action :
		{
			PUSH: 0,
			POP: 1
		},
		_event: function(action, state)
		{
			this.action = action;
			this.state = state;
		},
		
		
		push: function(state)
		{
			this._eventQueue.push(new this._event(this._action.PUSH, state));
		},
		
		pop: function(state)
		{
			this._eventQueue.push(new this._event(this._action.POP, state));
		},
		
		_handleEventQueue: function()
		{
			for(var i = 0; i < this._eventQueue.length; i++)
			{
				switch(this._eventQueue[i].action)
				{
					case this._action.PUSH:
						this._stateStack.push(this._eventQueue[i].state);
						break;
						
					case this._action.POP:
						this._stateStack.pop();
						break;
						
					default:
						break;
				}
			}
			

			
			this._eventQueue.length = 0;
		},
		
		update: function(dt)
		{
			for(var i = this._stateStack.length - 1; i >= 0; i--)
				if(this._stateStack[i].update(dt) === false)
					break;
					
			this._handleEventQueue();
		},
		
		render: function(canvasContext)
		{
			for(var i = 0; i < this._stateStack.length; i++)
				if(this._stateStack[i].render(canvasContext) === false)
					break;
		},
		
		handleInput: function(dt)
		{
			for(var i = this._stateStack.length - 1; i >= 0; i--)
				if(this._stateStack[i].handleInput(dt) === false)
					break;
		}		
	};

	return StateStack;
}();
