'use strict';

/**
 * \brief A rectangle with a position and size.
 */
var Rect = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Number left X-coordinate of left side.
	 * \param Number top Y-coordinate of top side.
	 * \param Number width Width of rectangle
	 * \param Number height Height of rectangle.
	 */
	function Rect(left, top, width, height) 
	{
		this.left = left || 0;
		this.top = top || 0;
		this.width = width || 0;
		this.height = height || 0;
	}
	
	Rect.prototype =
	{
		/**
		 * \brief Checks if a point is within this rectangle.
		 * 
		 * \param Number x X-coordinate of point.
		 * \param Number y Y-coordinate of point.
		 * 
		 * \returns Boolean True if the point is within the rectangle, else false.
		 */
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