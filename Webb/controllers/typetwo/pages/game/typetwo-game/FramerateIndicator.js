'use strict';

/**
 * \brief HTML-based framerate indicator module.
 * 
 * The indicator is not drawn onto the canvas, as
 * it is its own HTML element.
 * 
 * The framerate is averaged on the last X taken
 * framerate samples. See the filterStrength variable.
 * 
 * Toggle: CTRL+§
 */
var FramerateIndicator = function()
{
	var indicator = null; /**< DOM Shown indicator */
	var interval = null; /**< Function Interval function handle */
	var enabled = false; /**< Boolean Flag indicating whether the indicator is to be shown or not */ 
	var filterStrength = 10; /**< Number How many samples to take the average of */
	var frameTime = 0; /**< Number Duration of frame in milliseconds */
	var lastUpdateTime = Date.now(); /**< Last time indicator was updated */

	/**
	 * \brief Updates the indicator's shown value
	 */
	var updateIndicator = function()
	{
		indicator.html("FPS: " + (1000/frameTime).toFixed(1));
	};

	

	var my =  
	{
		/**
		 * \brief Enable indicator
		 */
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
		
		/**
		 * \brief Disable indicator
		 */
		disable: function()
		{
			enabled = false;
			indicator.detach();
			clearInterval(interval);
		},
		
		/**
		 * \brief Update indicator.
		 */
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
