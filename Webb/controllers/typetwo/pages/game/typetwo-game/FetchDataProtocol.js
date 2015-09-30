'use strict';

var FetchDataProtocol = function()
{
	function FetchDataProtocol()
	{
		WebSocketSubProtocol.call(this, 'fetch-data');
	};
	

	$.extend(FetchDataProtocol.prototype, WebSocketSubProtocol.prototype,
	{
		_parseMessage: function(message)
		{
			if(message.length <= 2)
				return null;
			
			var columns = message[0].split(',');
			var numColumns = columns.length;

			
			var output = [message[0].trim(',')];
			for(var i = 1; i < message.length; i += numColumns)
			{
				var row = '';
				for(var j = 0; j + i < message.length && j < numColumns; j++)
				{
					row += message[j + i] + '\t\t';
				}
				
				output.push(row);
			}
				
				
			
			var messageLength = message.length - 1;			
			return output;
		},
	});

	return FetchDataProtocol;
}();
