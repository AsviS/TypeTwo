'use strict';

var GameHudState = function()
{
	function GameHudState(stateStack, canvas)
	{
		State.call(this, stateStack);
		this._initialize(canvas);
	}


	$.extend(GameHudState.prototype, State.prototype,
	{
		_purchaseList: null,
		_unitList: null,
		_sideBar: null,
		
		render: function(ct)
		{
			this._sideBar.render(ct);
		},
		
		update: function(dt)
		{
			this._sideBar.update(dt);
		},
		
		handleInput: function(dt)
		{
			this._sideBar.handleInput(dt);
		},
		
		_initialize: function(canvas)
		{
			this._sideBar = new GUIList(new Vector(canvas.width * 3/4 + 2, 0));
			this._purchaseList = new GUIList();
			this._unitList = new GUIList();
			
			this._sideBar.appendElement(this._purchaseList);
			this._sideBar.appendElement(this._unitList);

			var self = this;
			GUIEvents.populatePurchaseList.registerCallback(function(zone)
			{
				for(var i in GameData.unitTypes.getMap())
				{
					var type = GameData.unitTypes.getMap()[i];
					
					if(type)
					{
						var buttonCallback = function(args){return function()
						{
							config.webSocket.order.sendQuery							
							(
									"unit",
									args,
									function(response)
									{
										response = response.data;
										if(response.success === true)
										{
											console.log("Unit purchase succeeded.");
											
											for(var i = 0; i < response.data.length; i++)
											{
												var unit = response.data[i];
												GameData.units.insert(unit.unit_id, unit);
											}

											GUIEvents.depopulateZoneUnitList.trigger();
											GUIEvents.populateZoneUnitList.trigger(zone);
										}
										else
											console.log("Unit purchase failed.");										
									},
									function()
									{
										console.log("Unit purchase timed out.");
									}
							);
						};}([type.unit_type_id, zone.getId()]);
						
						self._purchaseList.appendElement(new GUIButton
						(
							new Rect(0, 0, 100, 50), 
							[type.name],
							buttonCallback
						));
					}
				}
			});
			
			GUIEvents.depopulatePurchaseList.registerCallback(function(zone)
			{
				self._purchaseList.clear();
			});
			
			GUIEvents.populateZoneUnitList.registerCallback(function(zone)
			{
				var units = GameData.units.getMap();
				self._unitList.clear();
				for(var i in units)
				{
					var unit = units[i];
					
					if(unit.fk_unit_zoneid_zone == zone.getId())
					{
						var unitName = unit.fk_unit_unittypeid_unit_type === "1" ? "Fighter" : "Bomber";
						var user = GameData.users.get(unit.fk_unit_userid_user);

						var username = user ? user.username : "???";
						
						var text = new GUIText([username + "\t|\t" + unitName + "\t|\t" + unit.hp + "hp"]);
						text.setColor('white');
						
						self._unitList.appendElement(text);
					}
				}
			});
			
			GUIEvents.depopulateZoneUnitList.registerCallback(function(zone)
			{
				self._unitList.clear();
			});
		}
	});

	return GameHudState;
}();
