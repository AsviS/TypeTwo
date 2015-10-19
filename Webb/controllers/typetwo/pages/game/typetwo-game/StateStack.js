'use strict';

/**
 * \brief State stack containing State objects.
 */
var StateStack = function()
{
	/**
	 * \brief Constructor
	 */
	function StateStack()
	{
		this._stateStack = [];
		this._eventQueue = [];
	}


	StateStack.prototype =
	{
		_stateStack: null, /**< Array State stack */
		_eventQueue: null, /**< Array State request queue */
		
		/**
		 * \brief State request action type.
		 */
		_action :
		{
			PUSH: 0, /**< Push a specified State object to stack */
			POP: 1 /**< Pop the top State from stack */
		},
		
		/**
		 * \brief State request constructor
		 * 
		 * States may request a push or a pop from the state stack.
		 * 
		 * \param StateStack._action action Action type to execute.
		 * \param State state State to push, if the action type is PUSH.
		 */
		_event: function(action, state)
		{
			this.action = action;
			this.state = state || null;
		},
		
		/**
		 * \brief Insert a State to the top of the stack
		 * 
		 * \param State state State object to push
		 */
		push: function(state)
		{
			this._eventQueue.push(new this._event(this._action.PUSH, state));
		},
		
		/**
		 * \brief Remove the top State from the stack
		 */
		pop: function()
		{
			this._eventQueue.push(new this._event(this._action.POP));
		},
				
		/**
		 * \brief Call State objects' update functions.
		 * 
		 * \param Number dt Time per frame
		 */
		update: function(dt)
		{
			for(var i = this._stateStack.length - 1; i >= 0; i--)
				if(this._stateStack[i].update(dt) === false)
					break;
					
			this._handleEventQueue();
		},
		
		/**
		 * \brief Call State objects' render functions.
		 * 
		 * \param Canvas.context canvasContext Canvas context to draw to.
		 */
		render: function(canvasContext)
		{
			for(var i = 0; i < this._stateStack.length; i++)
				if(this._stateStack[i].render(canvasContext) === false)
					break;
		},
		
		/**
		 * \brief Call State objects' handleInput functions.
		 * 
		 * \param Number dt Time per frame.
		 */
		handleInput: function(dt)
		{
			for(var i = this._stateStack.length - 1; i >= 0; i--)
				if(this._stateStack[i].handleInput(dt) === false)
					break;
		},
		
		/***
		 * \brief Handle State requests
		 */
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
	};

	return StateStack;
}();
