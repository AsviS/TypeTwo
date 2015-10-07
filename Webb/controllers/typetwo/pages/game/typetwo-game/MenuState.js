'use strict';

/**
 * \brief Base class for states that show a menu
 */
var MenuState = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param StateStack stateStack
	 */
	function MenuState(stateStack)
	{
		State.call(this, stateStack);
		
		this._guiContainer = new GUIContainer();
	}

	$.extend(MenuState.prototype, State.prototype,
	{
	
		/**
		 * \brief Render state
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \returns Boolean
		 */
		render: function(ct)
		{
			this._guiContainer.render(ct);
			return true;
		},
				
		/**
		 * \brief Update state
		 * 
		 * \param Number dt Time per frame
		 * \returns Boolean
		 */
		update: function(dt)
		{
			this._guiContainer.update(dt);
			return false;
		},
		
		/**
		 * \brief Handle device input
		 * 
		 * \param Number dt Time per frame
		 * \returns Boolean
		 */
		handleInput: function(dt)
		{
			this._guiContainer.handleInput(dt);
			return false;
		},
	});
	
	return MenuState;
}();