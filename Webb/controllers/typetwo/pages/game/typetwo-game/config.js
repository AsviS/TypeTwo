'use strict';


/**
 * \brief Configuration settings for the game.
 * 
 * This data is commonly used throughout the codebase.
 */
var config = 
{
	/**
	 * \brief Initialize the configuration settings.
	 * 
	 * This function should be called after all dependancies have
	 * loaded.
	 */
	init: function()
	{
		config =
		{
			ASSETS_PATH: '../typetwo-game/assets', /**< String Path to asset files */
			webSocket: /**< Array WebSocket connections.*/
			{
				order: new Socket('localhost', 8080, new OrderProtocol()), 			/**< Socket Order connection. */
				chat: new Socket('localhost', 8080, 'chat'),						/**< Socket Chat connection. */
				fetchData: new Socket('localhost', 8080, new FetchDataProtocol()),	/**< Socket Fetch Data connection. */
			},
			canvas: new Canvas2D('typetwo-canvas'), /**< Canvas2D Canvas to draw to */
		};
	},
};
