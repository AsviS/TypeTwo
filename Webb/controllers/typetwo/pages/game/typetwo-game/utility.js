'use strict';
var utility = function()
{
	var my = {};
	my.getAbsPos = function(elementId)
	{
		var element = document.getElementById(elementId);
	
		var left = element.offsetLeft; 
		var top = element.offsetTop;
		
		
		
		while(element = element.offsetParent)
			left += element.offsetLeft;
			
		
			
		element = document.getElementById(elementId);
		while(element = element.offsetParent)
			top += element.offsetTop;
			
		return [left, top];
	};
	
	my.contains = function(left, top, width, height, pX, pY)
	{
		if(pX < left)
			return false;
		if(pX > left + width)
			return false;
		
		if(pY < top)
			return false;
		if(pY > top + height)
			return false;
			
		return true;
	};


	return my;
}();
