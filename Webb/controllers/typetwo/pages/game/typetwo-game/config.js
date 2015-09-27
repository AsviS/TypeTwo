'use strict';

var config = 
{
	init: function()
	{
		config =
		{
			ASSETS_PATH: '../typetwo-game/assets',
			webSocket:
			{
				order: new Socket('localhost', 8080, 'order'),
				fetchData: new Socket('localhost', 8080, 'fetchData'),
			},
			canvas: new Canvas2D('typetwo-canvas'),
		};
	},
};
