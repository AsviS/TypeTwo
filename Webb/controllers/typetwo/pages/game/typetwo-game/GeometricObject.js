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
			this._bounds.left = x - this._origin.x;
			this._bounds.top = y - this._origin.y;
		},
		
		setPositionVector: function(vector)
		{
			this._bounds.left = vector.x - this._origin.x;
			this._bounds.top = vector.y - this._origin.y;
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
	};

	return GeometricObject;
}();
