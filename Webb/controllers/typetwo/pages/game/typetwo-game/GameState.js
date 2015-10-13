'use strict';

var GameState = function()
{
	function GameState(stateStack, canvas)
	{
		State.call(this, stateStack);
		
		
		var gridWidth = canvas.width / 2;
		
		var gridBounds = new Rect((canvas.width - gridWidth) / 2, 0, gridWidth, canvas.height);
		
		this._gameGrid = new GameGrid(gridBounds, 9);
		this._purchaseList = new GUIList(new Vector(gridBounds.left + gridBounds.width + 2, 0));
		this._unitList = new GUIList(new Vector(gridBounds.left + gridBounds.width + 2, gridBounds / 2));
		
		var self = this;
		GUIEvents.populatePurchaseList.registerCallback(function(zone)
		{
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
		});
		
		GUIEvents.depopulatePurchaseList.registerCallback(function(zone)
		{
			self._purchaseList.clear();
		});
		
		GUIEvents.populateZoneUnitList.registerCallback(function(zone)
		{
			config.webSocket.fetchData.sendQuery
			(
				"getUnitsByZoneId\n" + zone.getId(), 
				function(response)
				{
					response = response.data;

					for(var i = 0; i < response.length; i++)
					{
						var unit = response[i];
						
						var unitName = unit.fk_unit_unittypeid_unit_type === "1" ? "Fighter" : "Bomber";
						
						var text = new GUIText([unit.unit_id + "\t|\t" + unitName + "\t|\t" + unit.hp + "hp"]);
						text.setColor('white');
						
						self._purchaseList.appendElement(text);
					}
						
				},
				function()
				{
					console.log("Could not fetch units at zone with ID '" + zone.getId() + "'.");
				}
			);
		});
		
		GUIEvents.depopulateZoneUnitList.registerCallback(function(zone)
		{
			self._unitList.clear();
		});
	}


	$.extend(GameState.prototype, State.prototype,
	{
		_gameGrid: null,
		_purchaseList: null,
		_unitList: null,
		
		render: function(ct)
		{
			ct.fillStyle = 'blue';
			ct.fillRect(0, 0, config.canvas.width, config.canvas.height);
			
			this._gameGrid.render(ct);
			this._purchaseList.render(ct);
		},
		
		update: function(dt)
		{
			this._gameGrid.update(dt);
			this._purchaseList.update(dt);
		},
		
		handleInput: function(dt)
		{
			this._gameGrid.handleInput(dt);
			this._purchaseList.handleInput(dt);
		}
	});

	return GameState;
}();
