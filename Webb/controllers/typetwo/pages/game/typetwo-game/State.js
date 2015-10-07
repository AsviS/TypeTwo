'use strict';

/**
 * \brief Base class for states in the StateStack
 */
var State = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param StateStack stateStack State stack that this state belongs to.
	 */
	function State(stateStack)
	{
		this._stateStack = stateStack;
	}

	
	State.prototype =
	{
		_stateStack: null, /**< State stack in which this state belongs to. */
		
		/**
		 * \brief Update state
		 * 
		 * \param Number dt Time per frame
		 * 
		 * \returns True if this state allows states beneath to be updated, else false.
		 */
		update: function(dt)
		{
			return true;
		},
	
		/**
		 * \brief Render state
		 * 
		 * \param Canvas.context ct Canvas context to draw state to.
		 * 
		 * \returns True if this state allows states above to be rendered, else false.
		 */
		render: function(ct)
		{
			return true;
		},
		
		/**
		 * \brief Handle device input
		 * 
		 * \param Number dt Time per frame
		 * 
		 * \returns True if this state allows states beneath to handle input, else false.
		 */
		handleInput: function(dt)
		{
			return true;
		},
	};



	return State;
}();
