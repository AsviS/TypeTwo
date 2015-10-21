'use strict';

var Zone = function()
{
	function Zone(id, bounds, parentZone, subZones, borderingZones)
	{
		GUIElement.call(this);
		
		this.setBounds(bounds);
		this._bounds.left += 2;
		this._bounds.top += 2;
		this._bounds.width -= 4;
		this._bounds.height -= 4;
		
		this._id = id;
		this._parentZone = parentZone || null;
		this._subZones = subZones || [];
		this._borderingZones = borderingZones || [];
	}


	$.extend(Zone.prototype, GUIElement.prototype,
	{
		_id: 0,
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

		_handleInputCurrent: function(dt)
		{
			if(Input.mouse.isPressed(Input.mouse.RIGHT))
			{
				for(var i = 0; i < this._borderingZones.length; i++)
					if(this._borderingZones[i].isActivated())
					{
						var startZone = this._borderingZones[i];
						var destinationZone = this;
						
						var args = [];
						var units = GameData.units.getMap();
						for(var j in units)
						{
							if(units[j].fk_unit_zoneid_zone == startZone.getId())
							{
								args.push(units[j].unit_id);
								args.push(destinationZone.getId());
							}
						}
						
						
						config.webSocket.order.sendQuery
						(
							"unitMove",
							args,
							function(response)
							{
								response = response.data;
								
								if(response.success)
								{
									for(var j = 0; j < args.length; j += 2)
									{										
										GameData.units.get(args[j]).fk_unit_zoneid_zone = destinationZone.getId();
									}
									
									GUIEvents.populateZoneUnitList.trigger(startZone);
									GUIEvents.populateZoneUnitList.trigger(destinationZone);
								}
								else
									console.log("Could not move unit(s).");
								
							},
							function()
							{
								console.log("Attempt to move unit(s) timed out.");
							}
						);
						
						break;
					}
						
			}
				
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
			
			GUIEvents.populatePurchaseList.trigger(this);
			GUIEvents.populateZoneUnitList.trigger(this);
			
			return true;
		},
		
		_deactivate: function()
		{	
			for(var i = 0; i < this._borderingZones.length; i++)
				this._borderingZones[i].neighborDeselect();
			
			GUIEvents.depopulatePurchaseList.trigger(this);
			GUIEvents.depopulateZoneUnitList.trigger(this);
			
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
		
		getId: function()
		{
			return this._id;
		}
	});

	return Zone;
}();
