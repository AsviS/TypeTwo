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
		_parseInMessage: function(message)
		{
			return this.parseDataString(message);
		},
		
		parseDataString: function(data)
		{
			if(data.length <= 1)
				return [];
			
			var columns = data[0].split(',');
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
			rows.length = (data.length - 1) / numColumns;
			for(var i = 1; i < data.length; i += numColumns)
			{
				var row = {};
				for(var j = 0; j + i < data.length && j < numColumns; j++)
					row[columnData[j].name] = data[j + i];
				
				rows[(i - 1) / numColumns] = row;
			}
		
			return rows;
		},
		
		_parseOutMessage: function(data)
		{
			return data.join('\n');
		},
	});

	return FetchDataProtocol;
}();
