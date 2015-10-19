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
					this._activateElement();
				else
					this._deactivateElement();
			}
			else if(Input.mouse.isPressed(Input.mouse.TAP))
			{
				var foundTarget = false;
				for(var i = this._children.begin(); i != this._children.end(); i = i.next)
				{
					if(i.data.isSelectable() && i.data.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
					{
						this._selectElement(i.data);
						this._activateElement();
						foundTarget = true;
					}
				}
				
				if(!foundTarget)
				{
					this._deactivateElement();
					this._deselectElement();
				}
			}
			
			if(this._hasActivation())
			{
				this._activation.handleInput();
				if(!this._activation.isActivated())
					this._deactivateElement();
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
					this._selectElement(i.data);
					return;
				}
			}
			
			// If we got here, it means that the cursor is not on any element.
			this._deselectElement();
		},
		
		/**
		 * \brief Select element.
		 * 
		 * \param GUIElement Element to select.
		 */
		_selectElement: function(element)
		{
			if(this._selection == element)
				return;
			
			this._deselectElement();
			element.select();
			this._selection = element;
		},
		
		/**
		 * \brief Deselect current selection, if any.
		 */
		_deselectElement: function()
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
		_activateElement: function()
		{
			if(this._activation === this._selection)
				return;
			
			this._deactivateElement();
			this._selection.activate();
			this._activation = this._selection;
		},
		
		/**
		 * \brief Deactivate currently activated element.
		 */
		_deactivateElement: function()
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
