'use strict';

var GameGrid = function()
{
	function GameGrid(bounds, numZones)
	{
		GUIContainer.call(this, [], bounds);
		
		this._initializeZones(numZones);

		
		var units = GameData.units.getMap();
		this._unitCounts = [];
		this._unitCounts.length = this._zones.length;
		
		for(var i = 0; i < this._unitCounts.length; i++)
			this._unitCounts[i] = 0;
		
		for(var unit in units)
			this._unitCounts[units[unit].fk_unit_zoneid_zone - 1]++;
			
		for(var i = 0; i < this._unitCounts.length; i++)
		{
			var text = new GUIText();
			text.setColor('white');
			this._zones[i].attachChild(text);
			
			if(this._unitCounts[i] > 0)
				text.setText([this._unitCounts[i]]);
			
			this._unitCounts[i] = text;			
		}
		
		var self = this;
		GUIEvents.populateZoneUnitList.registerCallback(function(zone)
		{
			var zoneId = zone.getId();
			var unitCount = 0;
			for(var unit in units)
				if(units[unit].fk_unit_zoneid_zone == zoneId)
					unitCount++;
					
			if(unitCount > 0)
				self._unitCounts[zone.getId() - 1].setText([unitCount]);
		});
			
	}
	
	$.extend(GameGrid.prototype, GUIContainer.prototype,
	{
		_zones: null,
		_unitCounts: null,
		
		
		_initializeZones: function(numZones)
		{
			var zoneSize = new Vector(this._bounds.width, this._bounds.height).div(numZones);
			
			
			this._zones = [];
			this._zones.length = numZones;		
				
			var numRows = this._bounds.height / zoneSize.y;
			var zonesPerRow = this._bounds.width / zoneSize.x;
			var i = 0;
			var bounds = new Rect(0, 0, zoneSize.x, zoneSize.y);
			for(var y = 0; y < numRows; y++)
			{
				for(var x = 0; x < zonesPerRow; x++)
				{
					this._zones[i] = new Zone(i + 1, bounds);
					this.attachChild(this._zones[i]);
					
					bounds.left += zoneSize.x;
					i++;
				}
				
				bounds.top += zoneSize.y;
				bounds.left = 0;
			}		
			
			i = 0;
			for(var y = 0; y < numRows; y++)
			{
				for(var x = 0; x < zonesPerRow; x++)
				{
					var borderingZones = [];
					
					if(y > 0)
						borderingZones.push(this._zones[i - zonesPerRow]);
					if(y < numRows - 1)
						borderingZones.push(this._zones[i + zonesPerRow]);
						
					if(x > 0)
						borderingZones.push(this._zones[i - 1]);
					if(x < zonesPerRow - 1)
						borderingZones.push(this._zones[i + 1]);
					
					this._zones[i].setBorderingZones(borderingZones);
					i++;
				}
			}
		},
		

		/**
		 * \brief Handle device input for elements.
		 * 
		 */
		handleInput: function()
		{
			if(Input.mouse.isPressed(Input.mouse.LEFT) && this.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
			{
				if(this._hasSelection())
					this._activateElement();
				else
					this._deactivateElement();
			}
			else if(Input.mouse.isPressed(Input.mouse.TAP))
			{
				var foundTarget = false;
				for(var i = this._children.begin(); i != this._children.end(); i = i.next)
				{
					if(i.data.isSelectable() && i.data.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
					{
						this._selectElement(i.data);
						this._activateElement();
						foundTarget = true;
					}
				}
				
				if(!foundTarget)
				{
					this._deactivateElement();
					this._deselectElement();
				}
			}
			
			if(this._hasActivation())
			{
				this._activation.handleInput();
				if(!this._activation.isActivated())
					this._deactivateElement();
			}
				
		},
	});

	return GameGrid;
}();
