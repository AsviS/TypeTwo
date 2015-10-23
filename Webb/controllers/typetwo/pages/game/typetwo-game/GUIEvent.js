'use strict';

/**
 * \brief A GUI event
 * 
 * Holds a list of callback functions that are
 * invoked whenever the event is triggered.
 */
var GUIEvent = function()
{
	/**
	 * \brief Constructor
	 */
	function GUIEvent()
	{
		this._callbacks = new List();
	}


	GUIEvent.prototype =
	{
		_callbacks: null, /**< Function Callback to invoke when event is triggered. */
		
		/**
		 * \brief Register a callback function to this event
		 * 
		 * This function will be called whenever this event is triggered.
		 * 
		 * \param Function callback
		 */
		registerCallback: function(callback)
		{
			this._callbacks.pushBack(callback);
		},
		
		/**
		 * \brief Remove a callback function from this event.
		 * 
		 * \param Function callback Function to remove.
		 */
		unregisterCallback: function(callback)
		{
			this._callbacks.remove(callback);
		},
		
		/**
		 * \brief Invoke all registered callback functions
		 * 
		 * \param Object callee The object from where the event is triggered.
		 */
		trigger: function(callee)
		{
			for(var i = this._callbacks.begin(); i != this._callbacks.end(); i = i.next)
				i.data(callee, arguments);
		}
	};

	return GUIEvent;
}();
