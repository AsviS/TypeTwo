var GUIElement = function()
{
	function GUIElement()
	{
		SceneNode.call(this);
	}

	GUIElement.prototype = 
	{
		_isSelected: false,
		_isActivated: false,
			
		select: function()
		{
			this._isSelected = true;
		},
		
		deselect: function()
		{
			this._isSelected = false;
		},
		
		isSelectable: function()
		{
			return false;
		},
		
		isSelected: function()
		{
			return this._isSelected;
		},
		
		activate: function()
		{
			this._isActivated = true;
		},
		
		deactivate: function()
		{	
			this._isActivated = false;
		},
		
		isActivated: function()
		{
			return this._isActivated;
		},
	};
	
	$.extend(GUIElement.prototype, SceneNode.prototype);


	return GUIElement;
}();
