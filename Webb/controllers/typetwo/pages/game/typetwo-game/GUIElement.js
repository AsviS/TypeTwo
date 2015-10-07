/**
 * \brief Base class for a GUI element.
 */
var GUIElement = function()
{
	/**
	 * \brief Constructor
	 */
	function GUIElement()
	{
		SceneNode.call(this);
	}

	GUIElement.prototype = 
	{
		_isSelected: false, /**< Boolean Flag indicating whether this element is selected or not. */
		_isActivated: false, /**< Boolean Flag indicating whether this element has been activated or not. */
			
		/**
		 * \brief Select this element
		 */
		select: function()
		{
			this._isSelected = true;
		},
		
		/**
		 * \brief Deselect this element.
		 */
		deselect: function()
		{
			this._isSelected = false;
		},
		
		/**
		 * \brief Is this element selectable?
		 * 
		 * \returns Boolean True if selectable, else false.
		 */
		isSelectable: function()
		{
			return false;
		},
		
		/**
		 * \brief Is this element currently selected?
		 * 
		 * \returns Boolean True if selected, else false.
		 */
		isSelected: function()
		{
			return this._isSelected;
		},
		
		/**
		 * \brief Activate this element
		 */
		activate: function()
		{
			this._isActivated = true;
		},
		
		/**
		 * \brief Deactivate this element
		 */
		deactivate: function()
		{	
			this._isActivated = false;
		},
		
		/**
		 * \brief Has this element been activated?
		 * 
		 * \returns Boolean True if activated, else false.
		 */
		isActivated: function()
		{
			return this._isActivated;
		},
	};
	
	$.extend(GUIElement.prototype, SceneNode.prototype);


	return GUIElement;
}();
