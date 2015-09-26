'use strict';
var Canvas2D = function()
{
	function Canvas2D(canvasId)
	{
		this._canvas = document.getElementById(canvasId);
		this.context = this._canvas.getContext('2d');
	
		this.width = this._canvas.width = $(document).width();
		this.height = this._canvas.height = $(document).height();

		Input.bindInput(canvasId);
	}
	

	Canvas2D.prototype =
	{

	};

	return Canvas2D;
}();
