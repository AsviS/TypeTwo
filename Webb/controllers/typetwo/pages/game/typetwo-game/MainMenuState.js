'use strict';

var MainMenuState = function()
{
	function MainMenuState(stateStack, canvas)
	{
		MenuState.call(this, stateStack);
		
		this._canvas = canvas;
		this._width = canvas.width;
		this._height = canvas.height;
		var buttonSize = new Vector(this._width/3, this._height/10);
		var centerX = this._width/2 - buttonSize.x/2;
		var self = this;

		this._background = new Image();
		this._background.src = config.ASSETS_PATH + '/wow.jpg';
		this._background.ready = false;
		this._background.onload = function()
		{
			this.ready = true;
		};
		this._background.onerror = function()
		{
			console.log("Could not load image.");
		};


	}

	$.extend(MainMenuState.prototype, MenuState.prototype,
	{		
		render: function(ct)
		{
			this.drawBackground(ct);
			this._guiContainer.render(ct);
		},
		
		drawBackground: function(ct)
		{
			if(this._background.ready)
				ct.drawImage(this._background, 0, 0, this._width, this._height);
		},
	});

	return MainMenuState;
}();
