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
				chat: new Socket('localhost', 8080, 'chat'),
				fetchData: new Socket('localhost', 8080, 'fetch-data'),
			},
			canvas: new Canvas2D('typetwo-canvas'),
		};
	},
};
