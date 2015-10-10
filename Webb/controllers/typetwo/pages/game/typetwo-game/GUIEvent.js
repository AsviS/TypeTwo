'use strict';

var GUIEvent = function()
{
	function GUIEvent(id)
	{
		this._id = id;
		this._callbacks = new List();
	}


	GUIEvent.prototype =
	{
		_id: 0,
		_callbacks: null,
		
		registerCallback: function(callback)
		{
			this._callbacks.pushBack(callback);
		},
		
		unregisterCallback: function(callback)
		{
			this._callbacks.remove(callback);
		},
		
		trigger: function(callee)
		{
			for(var i = this._callbacks.begin(); i != this._callbacks.end(); i = i.next)
				i.data(callee, arguments);
		}
	};

	return GUIEvent;
}();
