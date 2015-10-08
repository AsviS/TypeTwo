'use strict';

var Zone = function()
{
	function Zone(bounds, parentZone, subZones, borderingZones)
	{
		GUIElement.call(this);
		
		this.setBounds(bounds);
		this._bounds.left += 2;
		this._bounds.top += 2;
		this._bounds.width -= 4;
		this._bounds.height -= 4;
		
		
		this._parentZone = parentZone || null;
		this._subZones = subZones || [];
		this._borderingZones = borderingZones || [];
	}


	$.extend(Zone.prototype, GUIElement.prototype,
	{
		_parentZone: null,
		_subZones: null,
		_borderingZones: null,
		
		_isNeighborActivated: false,
		
		setBorderingZones: function(borderingZones)
		{
			this._borderingZones = borderingZones;
		},
		
		_renderCurrent: function(ct, transform)
		{			
			ct.fillStyle = 'black';
			ct.fillRect(transform.x, transform.y, this._bounds.width, this._bounds.height);
			
			if(this.isActivated())
				ct.strokeStyle = 'red';
			else if(this.isSelected())
				ct.strokeStyle = 'orange';
			else if(this._isNeighborActivated)
				ct.strokeStyle = 'yellow';
			else
				ct.strokeStyle = 'gray';
			
			ct.strokeWidth = 2;
			ct.strokeRect(transform.x, transform.y, this._bounds.width, this._bounds.height);
		},
		
		neighborSelect: function()
		{
			this._isNeighborActivated = true;
		},
		
		neighborDeselect: function()
		{
			this._isNeighborActivated = false;
		},
		
		_activate: function()
		{			
			for(var i = 0; i < this._borderingZones.length; i++)
				this._borderingZones[i].neighborSelect();
			
			return true;
		},
		
		_deactivate: function()
		{			
			for(var i = 0; i < this._borderingZones.length; i++)
				this._borderingZones[i].neighborDeselect();
			
			return true;
		},
		
		/**
		 * \brief Is this element selectable?
		 * 
		 * \returns Boolean True if selectable, else false.
		 */
		isSelectable: function()
		{
			return true;
		},
	});

	return Zone;
}();
