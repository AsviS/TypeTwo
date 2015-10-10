'use strict';

/**
 * \brief Container for GUI elements.
 * 
 * Handles all the elements' necessities,
 * like updating, rendering and input handling.
 */
var GUIContainer = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Array GUIElement objects.
	 * \param Rect Bounding box of this container.
	 */
	function GUIContainer(guiElements, bounds)
	{
		SceneNode.call(this);

		if(guiElements)
			for(var i = 0; i < guiElements.length; i++)
				this.attachChild(guiElements[i]);

		if(bounds)
			this.setBounds(bounds);
	}

	$.extend(GUIContainer.prototype, SceneNode.prototype,
	{
		_selection:		null, /**< GUIElement Currently selected element */
		_activation:	null, /**< GUIElement Currently activated element */
		
		/**
		 * \brief Update this node
		 * 
		 * \param Number dt Time per frame
		 */
		_updateCurrent: function(dt)
		{
			this._updateElements(dt);
		},

		/**
		 * \brief Handle device input for elements.
		 * 
		 */
		handleInput: function()
		{
			if(Input.mouse.isPressed(Input.mouse.LEFT))
			{
				if(this._hasSelection())
					this._activate();
				else
					this._deactivate();
			}
			else if(Input.mouse.isPressed(Input.mouse.TAP))
			{
				var foundTarget = false;
				for(var i = this._children.begin(); i != this._children.end(); i = i.next)
				{
					if(i.data.isSelectable() && i.data.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
					{
						this._select(i.data);
						this._activate();
						foundTarget = true;
					}
				}
				
				if(!foundTarget)
				{
					this._deactivate();
					this._deselect();
				}
			}
			
			if(this._hasActivation())
			{
				this._activation.handleInput();
				if(!this._activation.isActivated())
					this._deactivate();
			}
				
		},
		
		/**
		 * \brief Update elements
		 */
		_updateElements: function()
		{
			for(var i = this._children.begin(); i != this._children.end(); i = i.next)
			{
				if(i.data.isSelectable() && i.data.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
				{
					this._select(i.data);
					return;
				}
			}
			
			// If we got here, it means that the cursor is not on any element.
			this._deselect();
		},
		
		/**
		 * \brief Select element.
		 * 
		 * \param GUIElement Element to select.
		 */
		_select: function(element)
		{
			if(this._selection == element)
				return;
			
			this._deselect();
			element.select();
			this._selection = element;
		},
		
		/**
		 * \brief Deselect current selection, if any.
		 */
		_deselect: function()
		{
			if(!this._hasSelection())
				return;

			this._selection.deselect();
			this._selection = null;
		},
		
		/**
		 * \brief Does the container currently have a selected element?
		 * 
		 * \returns Boolean True if selection exists, else false.
		 */
		_hasSelection: function()
		{
			return (this._selection !== null);
		},
		
		/**
		 * \brief Activate currently selected element.
		 */
		_activate: function()
		{
			if(this._activation === this._selection)
				return;
			
			this._deactivate();
			this._selection.activate();
			this._activation = this._selection;
		},
		
		/**
		 * \brief Deactivate currently activated element.
		 */
		_deactivate: function()
		{
			if(!this._hasActivation())
				return;

			this._activation.deactivate();
			this._activation = null;
		},
		
		/**
		 * \brief Does the container currently have an activated element?
		 * 
		 * \returns Boolean True if activated element exists, else false.
		 */
		_hasActivation: function()
		{
			return (this._activation !== null);
		}
	});

	return GUIContainer;
}();
