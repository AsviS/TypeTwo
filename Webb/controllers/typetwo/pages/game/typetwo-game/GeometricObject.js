'use strict';

var GeometricObject = function()
{
	function GeometricObject()
	{
		this._bounds = new Rect();
		this._origin = new Vector();
	}


	GeometricObject.prototype =
	{	
		_bounds: null,
		_origin: null,
		
		setPosition: function(x, y)
		{
			this.setPositionX(x);
			this.setPositionY(y);
		},
		
		setPositionX: function(x)
		{
			this._bounds.left = x - this._origin.x;
		},
		
		setPositionY: function(y)
		{
			this._bounds.top = y - this._origin.y;
		},
		
		setPositionVector: function(vector)
		{
			this.setPosition(vector.x, vector.y);
		},
		
		setOrigin: function(x, y)
		{
			this._origin.x = x;
			this._origin.y = y;
		},
		
		setOriginVector: function(vector)
		{
			this._origin.x = vector.x;
			this._origin.y = vector.y;
		},
		
		moveX: function(x)
		{
			this._bounds.left += x;
		},
		
		moveY: function(y)
		{
			this._bounds.top += y;
		},
		
		move: function(x, y)
		{
			this.moveX(x);
			this.moveY(y);
		},
		
		moveVector: function(vector)
		{
			this.move(vector.x, vector.y);
		},
		
		centerOrigin: function()
		{
			this._origin.x = this._bounds.width / 2;
			this._origin.y = this._bounds.height / 2;
		},
		
		setSize: function(width, height)
		{
			this._bounds.width = width;
			this._bounds.height = height;
		},
		
		setSizeVector: function(vector)
		{
			this._bounds.width = vector.width;
			this._bounds.height = vector.height;
		},
		
		setBounds: function(bounds)
		{
			this._bounds.left = bounds.left;
			this._bounds.top = bounds.top;
			this._bounds.width = bounds.width;
			this._bounds.height = bounds.height;
		},
		
		getPosition: function()
		{
			return new Vector(this._bounds.left, this._bounds.top);
		},
		
		getBounds: function()
		{
			return this._bounds;
		},
		
		getSize: function()
		{
			return new Vector(this._bounds.width, this._bounds.height);
		},
		
		getOrigin: function()
		{
			return this._origin;
		},
	};

	return GeometricObject;
}();
