'use strict';

var GUIContainer = function()
{
	function GUIContainer(guiElements, bounds)
	{
		SceneNode.call(this);

		if(guiElements)
			for(var i = 0; i < guiElements.length; i++)
				this.attachChild(guiElements[i]);

		this._bounds = bounds;
	}

	$.extend(GUIContainer.prototype, SceneNode.prototype,
	{
		_selection:		null,
		_activation:	null,
		

		_updateCurrent: function(dt)
		{
			this._updateElements(dt);
		},

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
				for(var i = 0; i < this._children.length; i++)
				{
					var element = this._children[i];
					if(element.isSelectable() && element.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
					{
						this._select(element);
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
		
		_updateElements: function()
		{
			for(var i = 0; i < this._children.length; i++)
			{
				var element = this._children[i];
				if(element.isSelectable() && element.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
				{
					this._select(element);
					return;
				}
			}
			
			// If we got here, it means that the cursor is not on any element.
			this._deselect();
		},
		
		_select: function(element)
		{
			if(this._selection == element)
				return;
			
			this._deselect();
			element.select();
			this._selection = element;
		},
		
		_deselect: function()
		{
			if(!this._hasSelection())
				return;

			this._selection.deselect();
			this._selection = null;
		},
		
		_hasSelection: function()
		{
			return (this._selection !== null);
		},
		
		
		_activate: function()
		{
			if(this._activation === this._selection)
				return;
			
			this._deactivate();
			this._selection.activate();
			this._activation = this._selection;
		},
		
		_deactivate: function()
		{
			if(!this._hasActivation())
				return;

			this._activation.deactivate();
			this._activation = null;
		},
		
		_hasActivation: function()
		{
			return (this._activation !== null);
		}
	});

	return GUIContainer;
}();
