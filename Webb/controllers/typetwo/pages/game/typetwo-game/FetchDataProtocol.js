'use strict';

/**
 * \brief Subprotocol for fetching data from server
 */
var FetchDataProtocol = function()
{
	/**
	 * \brief Constructor
	 */
	function FetchDataProtocol()
	{
		WebSocketSubProtocol.call(this, 'fetch-data');
	};
	
	var DataTypes =
	{
		String: 12,
	};
	

	$.extend(FetchDataProtocol.prototype, WebSocketSubProtocol.prototype,
	{
		/**
		 * \brief Parse a message into conformity with the fetch data subprotocol.
		 * 
		 * \param String message Message to parse
		 * \returns Array Parsed message
		 */
		_parseMessage: function(message)
		{
			if(message.length <= 1)
				return [];
			
			var columns = message[0].split(',');
			var numColumns = columns.length;

			var columnData = [];
			columnData.length = numColumns;
			for(var i = 0; i < columns.length; i++)
			{
				var column = columns[i].split(' ');
				var dataType = column[0];
				var name = column[1];
				
				columnData[i] = 
				{
					name: name, 
					type: dataType
				};
			}
			
			var rows = [];
			rows.length = (message.length - 1) / numColumns;
			for(var i = 1; i < message.length; i += numColumns)
			{
				var row = {};
				for(var j = 0; j + i < message.length && j < numColumns; j++)
					row[columnData[j].name] = message[j + i];
				
				rows[(i - 1) / numColumns] = row;
			}
		
			return rows;
		},
	});

	return FetchDataProtocol;
}();
