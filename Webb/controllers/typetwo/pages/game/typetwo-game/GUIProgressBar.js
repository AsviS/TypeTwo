'use strict';

/**
 * \brief Progress bar
 */
var GUIProgressBar = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Rect bounds Bounding box of progress bar.
	 */
	function GUIProgressBar(bounds)
	{
		GUIElement.call(this);
		this.setBounds(bounds);
	}

	$.extend(GUIProgressBar.prototype, GUIElement.prototype,
	{
		_progress: 0, /**< Number Percentile progress of bar. */

		/**
		 * \brief Render this object
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 */		
		_renderCurrent: function(ct)
		{
			ct.fillStyle = 'orange';
			ct.fillRect(this._bounds.left, this._bounds.top, this._progress, this._bounds.height);
			
			
			ct.strokeStyle = 'gray';	
			ct.lineWidth = 5;
			ct.strokeRect(this._bounds.left, this._bounds.top, this._bounds.width, this._bounds.height);			
		},
		
		/**
		 * \brief Increment progress bar by specified percentage.
		 * 
		 * \param Number percent Percent to increment progress bar by.
		 */
		increment: function(percent)
		{
			this._progress += this._bounds.width * percent;
			
			if(this._progress >= this._bounds.width)
				this._progress = this._bounds.width;
		},
		
		/**
		 * \brief Has the progress bar reached 100% progress?
		 * 
		 * \returns Boolean True if progress bar has reached 100%, else false.
		 */
		isFinished: function()
		{
			return this._progress == this._bounds.width;
		},
	});

	return GUIProgressBar;
}();
