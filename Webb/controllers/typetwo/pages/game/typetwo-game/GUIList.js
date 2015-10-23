'use strict';

/**
 * \brief Organize GUI elements as a list
 */
var GUIList = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Vector position
	 */
	function GUIList(position)
	{
		GUIContainer.call(this);
		
		if(position)
			this.setPositionVector(position);
	}


	$.extend(GUIList.prototype, GUIElement.prototype, GUIContainer.prototype,
	{
		_gapThickness: 5, /**< Number Width of gap between each element */
		
		/**
		 * \brief Add a GUI element to the bottom of the list
		 * 
		 * \param GUIElement element
		 */
		appendElement: function(element)
		{			
			if(this._children.size() > 0)
			{
				element.setPosition(0, this._bounds.height + this._gapThickness);
				
				var elementSize = element.getSize();
				var listSize = this.getSize();
				
				if(elementSize.x > listSize.x)
					this.setSize(elementSize.x, listSize.y + elementSize.y + this._gapThickness);
				else
					this.setSize(listSize.x, listSize.y + elementSize.y + this._gapThickness);
			}
			else
			{
				element.setPosition(0, 0);
				this.setSizeVector(element.getSize());
			}
			
			this.attachChild(element);
		},
		
		/**
		 * \brief Update this node
		 * 
		 * \param Number dt Time per frame
		 */
		_updateCurrent: function(dt)
		{
			GUIContainer.prototype._updateCurrent.call(this, dt);
			this._pack();
		},
		
		/**
		 * \brief Adjust GUI element's positions
		 * 
		 * If a GUI element's size changes, all elements below it
		 * will have to be moved. 
		 */
		_pack: function()
		{
			var size = new Vector();
			for(var i = this._children.begin(); i != this._children.end(); i = i.next)
			{
				i.data.setPosition(0, size.y);
				
				var elementSize = i.data.getSize();
				if(elementSize.x > size.x)
					size.x = elementSize.x;
					
				size.y += elementSize.y + this._gapThickness;
			}
			
			size.y -= this._gapThickness;
			
			this.setSizeVector(size);
		},
		
		/**
		 * \brief Clear list 
		 */
		clear: function()
		{
			this._children.clear();
		},
		
		/**
		 * \brief Is this element selectable?
		 * 
		 * \returns Boolean True if selectable, else false.
		 */
		isSelectable: function()
		{
			return true;
		},
		
		
	});

	return GUIList;
}();
