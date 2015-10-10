'use strict';

/**
 * \brief Base class for geometric objects in a 2D environment
 * 
 * A geometric object has the following geometric properties:
 * - Bounding box
 * - Position
 * - Origin
 */
var GeometricObject = function()
{
	/**
	 * \brief Constructor
	 */
	function GeometricObject()
	{
		this._bounds = new Rect();
		this._origin = new Vector();
	}


	GeometricObject.prototype =
	{	
		_bounds: null, /**< Rect Bounding box */
		_origin: null, /**< Vector Origin to base any transformation on. */
		
		/**
		 * \brief Set position by X- and Y-coordinates
		 * 
		 * \param Number x X-coordinate of destination
		 * \param Number y Y-coordinate of destination
		 */
		setPosition: function(x, y)
		{
			this.setPositionX(x);
			this.setPositionY(y);
		},
		
		/**
		 * \brief Set position on X-axis
		 * 
		 * \param Number x X-coordinate to move to.
		 */
		setPositionX: function(x)
		{
			this._bounds.left = x - this._origin.x;
		},
		
		/**
		 * \brief Set position on Y-axis
		 * 
		 * \param Number y Y-coordinate to move to.
		 */
		setPositionY: function(y)
		{
			this._bounds.top = y - this._origin.y;
		},
		
		/**
		 * \brief Set position to a point defined by a vector.
		 * 
		 * \param Vector Point to move to.
		 */
		setPositionVector: function(vector)
		{
			this.setPosition(vector.x, vector.y);
		},
		
		/**
		 * \brief Set origin by X- and Y-coordinates
		 * 
		 * \param Number x X-coordinate to set origin to.
		 * \param Number y Y-coordinate to set origin to.
		 */
		setOrigin: function(x, y)
		{
			this._origin.x = x;
			this._origin.y = y;
		},
		
		/**
		 * \brief Set origin to a point defined by a vector.
		 * 
		 * \param Vector Point to set origin to.
		 */
		setOriginVector: function(vector)
		{
			this._origin.x = vector.x;
			this._origin.y = vector.y;
		},
		
		/**
		 * \brief Move along X-axis
		 * 
		 * \param Number x How many units to move along the X-axis.
		 */
		moveX: function(x)
		{
			this._bounds.left += x;
		},
		
		/**
		 * \brief Move along Y-axis
		 * 
		 * \param Number y How many units to move along the Y-axis.
		 */
		moveY: function(y)
		{
			this._bounds.top += y;
		},
		
		/**
		 * \brief Move along X- and Y-axis
		 * 
		 * \param Number x How many units to move along X-axis.
		 * \param Number y How many units to move along Y-axis.
		 */
		move: function(x, y)
		{
			this.moveX(x);
			this.moveY(y);
		},
		
		/**
		 * \brief Move along X- and Y-axis using a vector.
		 * 
		 * \param Vector How many units to move alond X- and Y-axis.
		 */
		moveVector: function(vector)
		{
			this.move(vector.x, vector.y);
		},
		
		/**
		 * \brief Set origin to the center of the bounding box.
		 */
		centerOrigin: function()
		{
			this._origin.x = this._bounds.width / 2;
			this._origin.y = this._bounds.height / 2;
		},
		
		/**
		 * \brief Set the size of the bounding box.
		 * 
		 * \param Number width New width of bounding box.
		 * \param Number height New height of bounding box.
		 */
		setSize: function(width, height)
		{
			this._bounds.width = width;
			this._bounds.height = height;
		},
		
		/**
		 * \brief Increment bounding box's size.
		 * 
		 * \param Number width Width to increment bounding box's width by.
		 * \param Number height Height to increment bounding box's height by.
		 */
		incrementSize: function(width, height)
		{
			this._bounds.width += width;
			this._bounds.height += height;
		},
		
		/**
		 * \brief Set the size of the bounding box with a vector.
		 * 
		 * \param Vector Vector containing new width and height as x and y values.
		 */
		setSizeVector: function(vector)
		{
			this._bounds.width = vector.x;
			this._bounds.height = vector.y;
		},
		
		/**
		 * \brief Set bounding box.
		 * 
		 * \param Rect New bounding box.
		 */
		setBounds: function(bounds)
		{
			this._bounds.left = bounds.left;
			this._bounds.top = bounds.top;
			this._bounds.width = bounds.width;
			this._bounds.height = bounds.height;
		},
		
		/**
		 * \brief Get global coordinates of origin.
		 * 
		 * \returns Vector Global coordinates of origin.
		 */
		getPosition: function()
		{
			return new Vector(this._bounds.left, this._bounds.top);
		},
		
		/**
		 * \brief Get global bounding box.
		 * 
		 * \returns Rect Global bounding box.
		 */
		getBounds: function()
		{
			return new Rect(this._bounds.left, this._bounds.top, this._bounds.width, this._bounds.height);
		},
		
		/**
		 * \brief Get size of bounding box.
		 * 
		 * \returns Bounding box size.
		 */
		getSize: function()
		{
			return new Vector(this._bounds.width, this._bounds.height);
		},
		
		/**
		 * \brief Get local coordinates of origin.
		 * 
		 * \returns Vector Local coordinates of origin.
		 */
		getOrigin: function()
		{
			return new Vector(this._origin.x, this._origin.y);
		},
	};

	return GeometricObject;
}();
