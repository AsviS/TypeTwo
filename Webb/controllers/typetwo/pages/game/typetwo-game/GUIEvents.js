'use strict';

/**
 * \brief Module for GUI event storage.
 */
var GUIEvents = function()
{
	var my = 
	{
		populatePurchaseList: new GUIEvent(), /**< GUIEvent Refresh purchase list in sidebar */
		depopulatePurchaseList: new GUIEvent(), /**< GUIEvent Clear purchase list in sidebar */
		populateZoneUnitList: new GUIEvent(), /**< GUIEvent Refresh list of zone's units in sidebar */
		depopulateZoneUnitList: new GUIEvent(), /**< GUIEvent Clear list of zone's units in sidebar */
	};
	

	return my;
}();
