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
				order: new Socket('localhost', 8080, new OrderProtocol()),
				chat: new Socket('localhost', 8080, 'chat'),
				fetchData: new Socket('localhost', 8080, new FetchDataProtocol()),
			},
			canvas: new Canvas2D('typetwo-canvas'),
		};
	},
};
