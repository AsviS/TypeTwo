'use strict';

/**
 * \brief Map data structure
 * 
 * There is a JavaScript Map object already. However,
 * it is not entirely supported yet by all browsers.
 * Until then, this class should do.
 */
var Map = function()
{
	/**
	 * \brief Constructor
	 */
	function Map()
	{
		this._map = {};
	}


	Map.prototype =
	{
		_map: null, /**< Object Internal object used as an associative array. */
		_size: 0, /**< Number Number of elements in map. */
		
		/**
		 * \brief Insert element into "id" index.
		 * 
		 * If an element of specified id already exists, it
		 * is overwritten.
		 * 
		 * \param Object id Unique identifier used to identify the element
		 * \param Object data Data to store as an element
		 */
		insert: function(id, data)
		{
			if(!this.exists(id))
				this._size++;
			
			this._map[id] = data;
		},
		
		/**
		 * \brief Remove element at "id" index.
		 * 
		 * \param Object id Identifier of element to remove.
		 */
		remove: function(id)
		{
			if(this.exists(id))
				this._size--;
			
			delete this._map[id];
		},
		
		/**
		 * \brief Get element at "id" index.
		 * 
		 * \returns Object Element at "id" index. Undefined if element does not exist.
		 */
		get: function(id)
		{
			return this._map[id];
		},
		
		/**
		 * \brief Clear map of all elements
		 */
		clear: function()
		{
			this._map = {};
			this._size = 0;
		},
		
		/**
		 * \brief Get internal associative array.
		 * 
		 * Useful for iteration.
		 * 
		 * \returns Object
		 */
		getMap: function()
		{
			return this._map;
		},
		
		/**
		 * \brief Get number of elements
		 * 
		 * \returns Number Number of elements in map
		 */
		size: function()
		{
			return this._size;
		},
		
		/**
		 * \brief Is there an element at "id" index?
		 * 
		 * \returns Boolean True if an element at specified index exists, else false.
		 */
		exists: function(id)
		{
			return !(typeof this._map[id] === 'undefined');
		},
	};

	return Map;
}();
