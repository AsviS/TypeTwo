'use strict';

var Rect = function()
{
	function Rect(left, top, width, height) 
	{
		this.left = left || 0;
		this.top = top || 0;
		this.width = width || 0;
		this.height = height || 0;
	}
	
	Rect.prototype =
	{
		containsPoint: function(x, y)
		{
			if(x < this.left)
				return false;
			if(x > this.left + this.width)
				return false;
			
			if(y < this.top)
				return false;
			if(y > this.top + this.height)
				return false;
				
			return true;
		},
	};

	return Rect;
}();