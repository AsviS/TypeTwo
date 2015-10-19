'use strict';

var GameGrid = function()
{
	function GameGrid(bounds, numZones)
	{
		GUIContainer.call(this, [], bounds);
		
		this._initializeZones(numZones);
		
		var self = this;
		config.webSocket.fetchData.sendQuery
		(
			"getVisibleUnits",
			function(response)
			{
				response = response.data;
				
				var unitCount = [];
				unitCount.length = self._zones.length;
				
				for(var i = 0; i < unitCount.length; i++)
					unitCount[i] = 0;
				
				for(var i = 0; i < response.length; i++)
					unitCount[response[i].fk_unit_zoneid_zone]++;
				
				for(var i = 0; i < unitCount.length; i++)
				{
					if(unitCount[i] > 0)
					{
						var text = new GUIText([unitCount[i]]);
						text.setColor('white');
						self._zones[i].attachChild(text);
					}
				}
			},
			function()
			{
				console.log("Could not fetch visible units.");
			}
		);
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
					this._zones[i] = new Zone(i, bounds);
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
					this._activate();
				else
					this._deactivate();
			}
			else if(Input.mouse.isPressed(Input.mouse.TAP))
			{
				var foundTarget = false;
				for(var i = this._children.begin(); i != this._children.end(); i = i.next)
				{
					if(i.data.isSelectable() && i.data.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
					{
						this._select(i.data);
						this._activate();
						foundTarget = true;
					}
				}
				
				if(!foundTarget)
				{
					this._deactivate();
					this._deselect();
				}
			}
			
			if(this._hasActivation())
			{
				this._activation.handleInput();
				if(!this._activation.isActivated())
					this._deactivate();
			}
				
		},
	});

	return GameGrid;
}();
