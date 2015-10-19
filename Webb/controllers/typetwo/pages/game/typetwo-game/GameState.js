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
				for(var i = 0; i < GameData.unitTypes.length; i++)
				{
					var type = GameData.unitTypes[i];
					
					if(type)
					{
						var buttonCallback = function(queryString){return function()
						{
							config.webSocket.order.sendQuery							
							(
									queryString,
									function(response)
									{
										console.log(response);
										
										if(response.data === true)
										{
											console.log("Unit purchase succeeded.");
											
											config.webSocket.fetchData.sendQuery
											(
												"getUnitsByZoneId\n" + zone.getId(),
												function(response)
												{
													response = response.data;
													
													for(var i = 0; i < response.length; i++)
														GameData.units[response[i].unit_id] = response[i];
													
													console.log("derp");
													
													GUIEvents.depopulateZoneUnitList.trigger();
													GUIEvents.populateZoneUnitList.trigger(zone);
												},
												function()
												{
													console.log("failed get units fetch by zone");
												}
											);
											
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
				
				/*
				config.webSocket.fetchData.sendQuery
				(
					"getUnitTypes", 
					function(response)
					{
						response = response.data;
						
						for(var i = 0; i < response.length; i++)
						{
							var buttonCallback = function(queryString){return function()
							{
								config.webSocket.order.sendQuery							
								(
										queryString,
										function(response)
										{
											console.log(response);
											
											if(response.data === true)
												console.log("Unit purchase succeeded.");
											else
												console.log("Unit purchase failed.");										
										},
										function()
										{
											console.log("Unit purchase timed out.");
										}
								);
							};}("unit\n" + response[i].name + "\n" + zone.getId());
							
							self._purchaseList.appendElement(new GUIButton
								(
									new Rect(0, 0, 100, 50), 
									[response[i].name],
									buttonCallback
								));
						}
							
					},
					function()
					{
						console.log("Could not fetch unit types.");
					}
				);
				*/
			});
			
			GUIEvents.depopulatePurchaseList.registerCallback(function(zone)
			{
				self._purchaseList.clear();
			});
			
			GUIEvents.populateZoneUnitList.registerCallback(function(zone)
			{
				for(var i = 1; i < GameData.units.length; i++)
				{
					var unit = GameData.units[i];
					if(unit && unit.fk_unit_zoneid_zone == zone.getId())
					{
						var unitName = unit.fk_unit_unittypeid_unit_type === "1" ? "Fighter" : "Bomber";
						
						var text = new GUIText([unit.unit_id + "\t|\t" + unitName + "\t|\t" + unit.hp + "hp"]);
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
