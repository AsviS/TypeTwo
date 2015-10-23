'use strict';

/**
 * \brief A zone!
 * 
 * A zone is a GUI element with neighboring zones.
 * It may have a parent zone and several subzones.
 * Each zone is unique and is bound by a unique identifier.
 */
var Zone = function()
{
	/**
	 * \brief Construct
	 * 
	 * \param Number id Unique identifier
	 * \param Rect bounds Bounding box
	 * \param Zone parentZone
	 * \param Array subZones Array of Zone objects
	 * \param Array borderingZones Array of Zone objects
	 */
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
		_id: 0, /**< Number Unique identifier */
		_parentZone: null, /**< Zone Parent zone */
		_subZones: null, /**< Array Array of Zone objects */
		_borderingZones: null, /**< Array Array of Zone objects */
		
		_isNeighborActivated: false, /**< Boolean Indicates whether a neighboring zone has been activated by the user. */
		
		/**
		 * \brief Set bordering zones
		 * 
		 * \param Array borderingZones Array of Zone objects.
		 */
		setBorderingZones: function(borderingZones)
		{
			this._borderingZones = borderingZones;
		},
		
		/**
		 * \brief Render this node
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
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

		/**
		 * \brief Handle device input for this node
		 * 
		 * \param Number dt Time per frame
		 */
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
									GUIEvents.depopulateZoneUnitList.trigger(startZone);
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
		
		/**
		 * \brief Called by a neighboring zone when it is activated.
		 */
		neighborSelect: function()
		{
			this._isNeighborActivated = true;
		},
		
		/**
		 * \brief Called by a neighboring zone when it is deactivated.
		 */
		neighborDeselect: function()
		{
			this._isNeighborActivated = false;
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
			for(var i = 0; i < this._borderingZones.length; i++)
				this._borderingZones[i].neighborSelect();
			
			GUIEvents.populatePurchaseList.trigger(this);
			GUIEvents.populateZoneUnitList.trigger(this);
			
			return true;
		},
		
		/**
		 * \brief Deactivate this element
		 */
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
		
		/**
		 * \brief Get unique zone identifier
		 * 
		 * \returns Number This zone's identifier.
		 */
		getId: function()
		{
			return this._id;
		}
	});

	return Zone;
}();
