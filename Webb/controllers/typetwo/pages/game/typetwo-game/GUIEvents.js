'use strict';

var GUIEvents = function()
{
	var my = 
	{
		populatePurchaseList: new GUIEvent(0),
		depopulatePurchaseList: new GUIEvent(1),
		populateZoneUnitList: new GUIEvent(2),
		depopulateZoneUnitList: new GUIEvent(3),
	};
	

	return my;
}();
