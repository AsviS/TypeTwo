'use strict';

var GameState = function()
{
	function GameState(stateStack, canvas)
	{
		State.call(this, stateStack);
		
		GameData.init();
		
		this._gameGrid = new GUIElement();
		this._sideBar = new GUIList();
		
		var self = this;
		stateStack.push(new LoadingState
		(
			stateStack,
			canvas,
			GameData.isReady,
			function(){self._initialize(canvas);}
		));
	}


	$.extend(GameState.prototype, State.prototype,
	{
		_gameGrid: null,
		_purchaseList: null,
		_unitList: null,
		_sideBar: null,
		
		render: function(ct)
		{
			ct.fillStyle = 'blue';
			ct.fillRect(0, 0, config.canvas.width, config.canvas.height);
			
			this._gameGrid.render(ct);
			this._sideBar.render(ct);
		},
		
		update: function(dt)
		{
			this._gameGrid.update(dt);
			this._sideBar.update(dt);
		},
		
		handleInput: function(dt)
		{
			this._gameGrid.handleInput(dt);
			this._sideBar.handleInput(dt);
		},
		
		_initialize: function(canvas)
		{
			var gridWidth = canvas.width / 2;
				
			var gridBounds = new Rect((canvas.width - gridWidth) / 2, 0, gridWidth, canvas.height);
			
			this._gameGrid = new GameGrid(gridBounds, 3);
			this._sideBar = new GUIList(new Vector(gridBounds.left + gridBounds.width + 2, 0));
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
						var buttonCallback = function(queryString){return function()
						{
							config.webSocket.order.sendQuery							
							(
									queryString,
									null,
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
						};}("unit\n" + type.name + "\n" + zone.getId());
						
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

	return GameState;
}();
