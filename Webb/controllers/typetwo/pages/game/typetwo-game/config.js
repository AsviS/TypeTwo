'use strict';

var config = 
{
	ASSETS_PATH: '../typetwo-game/assets',
	webSocket:
	{
		order: new Socket('mikael.hernvall.com', 8080, 'order'),
		fetchData: new Socket('mikael.hernvall.com', 8080, 'fetchData'),
	},
};
