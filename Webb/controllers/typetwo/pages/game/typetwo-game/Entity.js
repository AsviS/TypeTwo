'use strict';

var Entity = function()
{
	function Entity(zone)
	{
		SceneNode.call(this);
		
		this._zone = zone;
	}


	$.extend(Entity.prototype, SceneNode.prototype,
	{
		_zone: null,
	});

	return Entity;
}();
