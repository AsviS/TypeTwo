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
	
	function Column(name, type)
	{
		this.name = name;
		this.type = type;
	}
	
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
			if(data.length <= 2)
				return [];
			
			var columns = FetchDataProtocol.prototype.parseDataColumns(data);

			return FetchDataProtocol.prototype.parseDataRows(data, columns);
		},
		
		parseDataColumns: function(data)
		{
			var columns = data[0].split(',');

			var columnData = [];
			columnData.length = columns.length;
			for(var i = 0; i < columns.length; i++)
			{
				var column = columns[i].split(' ');
				var dataType = column[0];
				var name = column[1];
				
				columnData[i] = new Column(name, dataType);
			}
			
			return columnData;
		},
		
		parseDataRows: function(data, columns)
		{
			var rows = [];
			rows.length = (data.length - 1) / columns.length;
			var rowIndex = 0;
			for(var i = 1; i < data.length; i += columns.length)
			{
				var row = {};
				for(var j = 0; j + i < data.length && j < columns.length; j++)
					row[columns[j].name] = data[j + i];
				
				rows[rowIndex] = row;
				rowIndex++;
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
