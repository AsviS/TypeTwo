'use strict';

/**
 * \brief Wraps a 2D HTML5 Canvas element.
 * 
 * Takes care of the Canvas' bounds and
 * device input.
 */
var Canvas2D = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param String canvasId ID of HTML5 Canvas element.
	 */
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
