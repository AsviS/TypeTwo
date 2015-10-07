'use strict';

/**
 * \brief Manages queries done on a WebSocket connection.
 * 
 * Since the time delay between query and response can be 
 * quite large, the manager's job is to piece together query
 * and response by ID numbers.
 */
var WebSocketQueryManager = function()
{
	/**
	 * \brief Internal Query object constructor
	 * 
	 * \param Number id ID number of this query.
	 * \param Function success Function to call when query received a response.
	 * \param Function fail Function to call when query did not receive a response.
	 * \param Number timeOut Time in milliseconds to wait before dropping the query.
	 */
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
		id: null, /**< Number ID of query. The ID is used to piece together query and response. */
		onSuccess: null, /**< Function Function to call when query received a response. */
		onFail: null, /**< Function Function to call when query did not receive a response.*/
		timeOut: 5000, /**< Time in milliseconds to wait before dropping the query. */
		timeCreated: null, /**< Time when query was sent */
	};

	/**
	 * The query manager is actually a List with some extended functionality.
	 */
	function QueryList()
	{
		List.call(this);
	};

	$.extend(QueryList.prototype, List.prototype,
	{
		_maxTimeOut: 10000, /**< Maximum time to wait in milliseconds before dropping any query */
		
		/**
		 * \brief On response, scan the list for a query with matching ID number.
		 * 
		 * If found, execute that query's success callback.
		 * While scanning through the list, drop any timed out queries.
		 * 
		 * \param Number id ID number of query.
		 * \param Object response Response to query.
		 */
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
		
		/**
		 * \brief Add a query to the list and return its designated ID number.
		 * 
		 * \param Function success Function to call when query received a response.
		 * \param Function fail Function to call when query did not receive a response.
		 * \param Number timeOut Time in milliseconds to wait before dropping the query.
		 * 
		 * \returns Number The query's designated ID number.
		 */
		pushQuery: function(success, fail, timeOut)
		{
			var id = this._back ? (this._back.data.id + 1) % Number.MAX_SAFE_INTEGER : 1;
			this.pushBack(new Query(id, success, fail, timeOut));
			return id;
		},
		
		/**
		 * \brief Update list.
		 */
		update: function()
		{
			this.onQueryResponse(0);
		},
	
		/**
		 * \brief Check if query is timed out.
		 * 
		 * \param Query query Query to check.
		 * 
		 * \returns True if query is timed out, else false.
		 */
		_isQueryTimedOut: function(query)
		{
			var lifeTime = Date.now() - query.timeCreated;
			
			return (lifeTime > query.timeOut || lifeTime > this._maxTimeOut);
		},
	});
	

	return new QueryList();
}();
