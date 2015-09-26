'use strict';

var FramerateIndicator = function()
{
	var indicator = null;
	var interval = null;
	var enabled = false;
	var filterStrength = 10;
	var frameTime = 0;
	var lastUpdateTime = Date.now();

	
	var updateIndicator = function()
	{
		indicator.html("FPS: " + (1000/frameTime).toFixed(1));
	};

	

	var my =  
	{
		enable: function()
		{
			enabled = true;
			$('body').append('<p id="framerate-indicator"></p>');
			indicator = $('#framerate-indicator');
			indicator.css(
			{
				position: 'absolute',
				left: 0,
			    top: 0,
			    margin: '0.5em 0 0 0.5em',
			    padding: 0,
			    position: 'absolute',			
			});
			updateIndicator();
			interval = setInterval(updateIndicator, 1000);
		},
		
		disable: function()
		{
			enabled = false;
			indicator.detach();
			clearInterval(interval);
		},
		
		update: function()
		{
			frameTime += (Date.now() - lastUpdateTime - frameTime) / filterStrength;
			lastUpdateTime = Date.now();
			if(Input.key.isPressed(Input.key.PARAGRAPH))
			{
				if(Input.key.isDown(Input.key.CONTROL))
				{
					if(enabled)
						my.disable();
					else
						my.enable();
				}
			}
		},
	};
	
	return my;
}();
