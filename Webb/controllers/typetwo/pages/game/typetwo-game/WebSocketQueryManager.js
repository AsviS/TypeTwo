'use strict';


var WebSocketQueryManager = function()
{
	function Query(id, success, fail, timeOut)
	{
		this.id = id;
		this.onSuccess = success || function(){};
		this.onFail = fail || function(){};
		this.timeOut = timeOut || this.timeOut;
		this.timeCreated = Date.now();
	};

	Query.prototype = 
	{
		id: null,
		onSuccess: null,
		onFail: null,
		timeOut: 5000,
		timeCreated: null,
	};

	function QueryList()
	{
		List.call(this);
	};

	$.extend(QueryList.prototype, List.prototype,
	{
		_maxTimeOut: 10000,
		
		onQueryResponse: function(id, response)
		{
			if(!this._front)
				return;
				
			var i = this._front;
			do
			{	
				if(this._isQueryTimedOut(i.data))
				{
					i.data.onFail();
					this._removeNode(i);
					
					
					if(i.data.id == id)
						return;
				}
				else if(i.data.id == id)
				{
					i.data.onSuccess(response);
					this._removeNode(i);
					return;
				}

				i = i.next;
			} while(i);
		},
		
		pushQuery: function(success, fail, timeOut)
		{
			var id = this._back ? (this._back.data.id + 1) % Number.MAX_SAFE_INTEGER : 1;
			this.pushBack(new Query(id, success, fail, timeOut));
			return id;
		},
		
		update: function()
		{
			this.onQueryResponse(0);
		},

		_isQueryTimedOut: function(query)
		{
			var lifeTime = Date.now() - query.timeCreated;
			
			return (lifeTime > query.timeOut || lifeTime > this._maxTimeOut);
		},
	});
	

	return new QueryList();
}();
