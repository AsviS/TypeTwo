'use strict';

var GUIProgressBar = function()
{

	function GUIProgressBar(bounds)
	{
		GUIElement.call(this);
		this.setBounds(bounds);
	}

	$.extend(GUIProgressBar.prototype, GUIElement.prototype,
	{
		_progress: 0,
		
		_renderCurrent: function(ct)
		{
			ct.fillStyle = 'orange';
			ct.fillRect(this._bounds.left, this._bounds.top, this._progress, this._bounds.height);
			
			
			ct.strokeStyle = 'gray';	
			ct.lineWidth = 5;
			ct.strokeRect(this._bounds.left, this._bounds.top, this._bounds.width, this._bounds.height);			
		},
		
		increment: function(percent)
		{
			this._progress += this._bounds.width * percent;
			
			if(this._progress >= this._bounds.width)
				this._progress = this._bounds.width;
		},
		
		isFinished: function()
		{
			return this._progress == this._bounds.width;
		},
	});

	return GUIProgressBar;
}();
