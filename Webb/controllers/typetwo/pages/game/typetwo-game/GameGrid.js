'use strict';

var GameGrid = function()
{
	function GameGrid(bounds, numZones)
	{
		GUIContainer.call(this, [], bounds);
		
		this._initializeZones(numZones);
	}
	
	$.extend(GameGrid.prototype, GUIContainer.prototype,
	{
		_zones: null,
		
		
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
					this._zones[i] = new Zone(bounds);
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
	});

	return GameGrid;
}();
