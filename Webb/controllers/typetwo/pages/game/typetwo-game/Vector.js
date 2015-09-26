'use strict';
var Vector = function()
{
	function Vector(x, y) 
	{
		this.x = x || 0;
		this.y = y || 0;
	}


	Vector.add = function(vector1, vector2)
	{
		return new Vector(vector1.x + vector2.x, vector1.y + vector2.y);
	};
	
	Vector.sub = function(vector1, vector2)
	{
		return new Vector(vector1.x - vector2.x, vector1.y - vector2.y);
	};
	
	Vector.div = function(vector, divisor)
	{
		return new Vector(vector.x / divisor, vector.y / divisor);
	};

	Vector.prototype =
	{
		addVector: function(vector)
		{
			this.x += vector.x;
			this.y += vector.y;
			
			return this;
		},
		
		subVector: function(vector)
		{
			this.x -= vector.x;
			this.y -= vector.y;
			
			return this;
		},
		
		add: function(x, y)
		{
			this.x += x;
			this.y += y;
			
			return this;
		},
		
		sub: function(x, y)
		{
			this.x -= x;
			this.y -= y;
			
			return this;
		},
		
		div: function(divisor)
		{
			this.x /= divisor;
			this.y /= divisor;
			
			return this;
		},
	};

	return Vector;
}();