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
			if(this._select() === true)
				this._isSelected = true;
		},
		
		/**
		 * \brief Select this element.
		 * 
		 * This function is used by inheriting classes.
		 * 
		 * \returns Boolean True if operation was successful, else false.
		 */
		_select: function()
		{
			return true;
		},
		
		/**
		 * \brief Deselect this element.
		 */
		deselect: function()
		{
			if(this._deselect() === true)
				this._isSelected = false;
		},
		
		/**
		 * \brief Deselect this element.
		 * 
		 * This function is used by inheriting classes.
		 * 
		 * \returns Boolean True if operation was successful, else false.
		 */
		_deselect: function()
		{
			return true;
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
			if(this._activate() === true)
				this._isActivated = true;
		},
		
		/**
		 * \brief Activate this element
		 * 
		 * This function is used by inheriting classes.
		 * 
		 * \returns Boolean True if operation was successful, else false.
		 */
		_activate: function()
		{
			return true;
		},
		
		/**
		 * \brief Deactivate this element
		 */
		deactivate: function()
		{	
			if(this._deactivate() === true)
				this._isActivated = false;
		},
		
		/**
		 * \brief Deactivate this element
		 * 
		 * This function is used by inheriting classes.
		 * 
		 * \returns Boolean True if operation was successful, else false.
		 */
		_deactivate: function()
		{
			return true;
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
