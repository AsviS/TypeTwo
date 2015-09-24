'use strict';
var Vector = function()
{
	function Vector(x, y) 
	{
		this.x = x || 0;
		this.y = y || 0;
	}


	Vector.prototype =
	{
		
	};

	return Vector;
}();


var Rect = function()
{
	function Rect(left, top, width, height) 
	{
		this.left = left || 0;
		this.top = top || 0;
		this.width = width || 0;
		this.height = height || 0;
	}

	return Rect;
}();

