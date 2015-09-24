'use strict';
var Canvas2D = function()
{
	function Canvas2D(canvasId)
	{
		this._canvas = document.getElementById(canvasId);
		this.context = this._canvas.getContext('2d');
		
		this.width = this._canvas.getAttribute('width').replace('px','');
		this.height = this._canvas.getAttribute('height').replace('px','');
		this.fontSize = this.width < this.height ? this.width/25 : this.height/25;
		this.context.font = 'bold ' + this.fontSize + 'px sans-serif';
		
		Input.bindInput(canvasId);
	}


	Canvas2D.prototype =
	{

	};

	return Canvas2D;
}();
