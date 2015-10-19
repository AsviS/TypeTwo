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
			function(response)
			{
				my.units = [];
				response = response.data;
				
				for(var i = 0; i < response.length; i++)
					my.units[response[i].unit_id] = response[i];
					
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
			function(response)
			{
				my.unitTypes = [];
				response = response.data;
				
				for(var i = 0; i < response.length; i++)
					my.unitTypes[response[i].unit_type_id] = response[i];
					
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
		/*
		database.sendQuery
		(
			"getZones"
			
		);*/
		numFinishedInitFunctions++;
	}
	
	var initFunctions = 
	[
		initUnits,
		initUnitTypes,
		initZones,
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
