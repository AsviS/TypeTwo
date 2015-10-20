'use strict';

var GUIList = function()
{
	function GUIList(position)
	{
		GUIContainer.call(this);
		
		if(position)
			this.setPositionVector(position);
	}


	$.extend(GUIList.prototype, GUIElement.prototype, GUIContainer.prototype,
	{
		_gapThickness: 5,
		
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
		
		_updateCurrent: function(dt)
		{
			GUIContainer.prototype._updateCurrent.call(this, dt);
			this._pack();
		},
		
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
