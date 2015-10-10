'use strict';

var GUIList = function()
{
	function GUIList(position)
	{
		GUIContainer.call(this);
		
		if(position)
			this.setPositionVector(position);
	}


	$.extend(GUIList.prototype, GUIContainer.prototype,
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
		
		clear: function()
		{
			this._children.clear();
		}
	});

	return GUIList;
}();
