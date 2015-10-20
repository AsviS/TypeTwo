'use strict';

var Map = function()
{
	function Map()
	{
		this._map = {};
	}


	Map.prototype =
	{
		_map: null,
		_size: 0,
		
		insert: function(id, data)
		{
			if(!this.exists(id))
				this._size++;
			
			this._map[id] = data;
		},
		
		remove: function(id)
		{
			if(this.exists(id))
				this._size--;
			
			delete this._map[id];
		},
		
		get: function(id)
		{
			return this._map[id];
		},
		
		clear: function()
		{
			this._map = {};
			this._size = 0;
		},
		
		getMap: function()
		{
			return this._map;
		},
		
		size: function()
		{
			return this._size;
		},
		
		exists: function(id)
		{
			return !(typeof this._map[id] === 'undefined');
		},
	};

	return Map;
}();
