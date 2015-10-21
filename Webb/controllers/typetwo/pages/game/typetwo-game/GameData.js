'use strict';

var GameData = function()
{
	var my = {};

	var database = null;

	var numFinishedInitFunctions = 0;

	function initUnits()
	{
		database.sendQuery
		(
			"getVisibleUnits",
			null,
			function(response)
			{
				var units = response.data;
				
				my.units = new Map();
				for(var i = 0; i < units.length; i++)
					my.units.insert(units[i].unit_id, units[i]);
					
				numFinishedInitFunctions++;
			},
			function()
			{
				console.log("Could not fetch visible units.");
			}
		);
	}
	
	
	function initUnitTypes()
	{
		database.sendQuery
		(
			"getUnitTypes",
			null,
			function(response)
			{
				var types = response.data;
				
				my.unitTypes = new Map();
				for(var i = 0; i < types.length; i++)
					my.unitTypes.insert(types[i].unit_type_id, types[i]);
					
				numFinishedInitFunctions++;		
			},
			function()
			{
				console.log("Could not fetch unit types.");
			}
		);
	}
	
	function initZones()
	{
		database.sendQuery
		(
			"getZones",
			null,
			function(response)
			{
				var zones = response.data;

				my.zones = new Map();
				for(var i = 0; i < zones.length; i++)
				{
					var zoneId = zones[i].zone_id;
					var neighborId = zones[i].neighbor_id;

					var zone = my.zones.get(zoneId);
					
					if(!zone)
					{
						zone = 
						{
							id: zoneId,
							neighbors: []
						};
						my.zones.insert(zoneId, zone);
					}
					

					zone.neighbors.push(neighborId);
				}

				numFinishedInitFunctions++;
			},
			function()
			{
				console.log("Could not fetch zones.");
			}
		);
	}
	
	function initUsers()
	{
		database.sendQuery
		(
			"getUsers",
			null,
			function(response)
			{
				var users = response.data;
				
				my.users = new Map();
				for(var i = 0; i < users.length; i++)
					my.users.insert(users[i].user_id, users[i]);				
			},
			function()
			{
				console.log("Could not fetch users.");
			}
		);
		
		numFinishedInitFunctions++;
	}
	
	var initFunctions = 
	[
		initUnits,
		initUnitTypes,
		initZones,
		initUsers,
	];
	
	my.init = function()
	{
		database = config.webSocket.fetchData;
		
		for(var i = 0; i < initFunctions.length; i++)
			initFunctions[i]();
		
		delete this.init;
	};
	
	my.isReady = function()
	{
		return numFinishedInitFunctions === initFunctions.length;
	};
	
	return my;
}();
