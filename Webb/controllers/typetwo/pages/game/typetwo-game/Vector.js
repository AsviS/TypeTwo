'use strict';

/**
 * \brief Vector
 */
var Vector = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Number x X-value
	 * \param Number y Y-value
	 */
	function Vector(x, y) 
	{
		this.x = x || 0;
		this.y = y || 0;
	}

	/**
	 * \brief Add two vectors together
	 * 
	 * \param Vector vector1
	 * \param Vector vector2
	 * 
	 * \returns Vector Sum vector
	 */
	Vector.add = function(vector1, vector2)
	{
		return new Vector(vector1.x + vector2.x, vector1.y + vector2.y);
	};
	
	/**
	 * \brief Subtract two vectors
	 * 
	 * \param Vector vector1 Vector to be subtracted
	 * \param Vector vector2 Vector to subtract with
	 * 
	 * \returns Vector Result of (vector1 - vector2)
	 */
	Vector.sub = function(vector1, vector2)
	{
		return new Vector(vector1.x - vector2.x, vector1.y - vector2.y);
	};
	
	/**
	 * \brief Divide a vector by a scalar
	 * 
	 * \param Vector Vector to divide
	 * \param Number divisor Scalar to divide with
	 * 
	 * \returns Vector Quotient vector of division.
	 */
	Vector.div = function(vector, divisor)
	{
		return new Vector(vector.x / divisor, vector.y / divisor);
	};

	Vector.prototype =
	{
		x: 0, /**< X-value */
		y: 0, /**< Y-value */
		
		/**
		 * \brief Add a vector to this vector
		 * 
		 * \param Vector vector Vector to add to this vector.
		 * 
		 * \returns Vector This vector.
		 */
		addVector: function(vector)
		{
			this.x += vector.x;
			this.y += vector.y;
			
			return this;
		},
		
		/**
		 * \brief Subtract a vector from this vector.
		 * 
		 * \param Vector vector Vector to subtract from this vector.
		 * 
		 * \returns Vector This vector.
		 */
		subVector: function(vector)
		{
			this.x -= vector.x;
			this.y -= vector.y;
			
			return this;
		},
		
		/**
		 * \brief Add X- and Y-values to this vector.
		 * 
		 * \param Number x X-value to add
		 * \param Number y Y-value to add
		 * 
		 * \returns Vector This vector.
		 */
		add: function(x, y)
		{
			this.x += x;
			this.y += y;
			
			return this;
		},
		
		/**
		 * \brief Subtract X- and Y-values from this vector.
		 * 
		 * \param Number x X-value to subtract
		 * \param Number y Y-value to subtract
		 * 
		 * \returns Vector This vector.
		 */
		sub: function(x, y)
		{
			this.x -= x;
			this.y -= y;
			
			return this;
		},
		
		/**
		 * \brief Divide this vector with a scalar.
		 * 
		 * \param Number divisor Scalar to divide with.
		 * 
		 * \returns Vector This vector.
		 */
		div: function(divisor)
		{
			this.x /= divisor;
			this.y /= divisor;
			
			return this;
		},
	};

	return Vector;
}();