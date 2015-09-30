'use strict';

var List = function()
{
	function List()
	{
	};

	function Node(data, previous, next)
	{
		this.data = data;
		this.previous = previous || null;
		this.next = next || null;
	};

	List.prototype = 
	{
		_front: null,
		_back: null,
		_size: 0,

		pushBack: function(data)
		{
			if(this._back)
				this._back = this._back.next = new Node(data, this._back, null);
			else
				this._front = this._back = new Node(data);
			
			this._size++;
		},

		pushFront: function(data)
		{
			if(this._front)
				this._front = this._front.previous = new Node(data, null, this._front);
			else
				this._front = this._back = new Node(data);
			
			this._size++;
		},

		popBack: function()
		{
			if(size > 1)
			{
				this._back = this._back.previous;
				
				this._back.next.next = null;
				this._back.next.previous = null;
				this._back.next = null;
				
				this._size--;
			}
			else if(size == 1)
				this.clear();
		},

		popFront: function()
		{
			if(this._size > 1)
			{
				this._front = this._front.next;
				
				this._front.previous.previous = null;
				this._front.previous.next = null;
				this._front.previous = null;
				
				this._size--;
			}
			else if(this._size == 1)
				this.clear();
		},
		
		clear: function()
		{
			this._front = this._back = null; // All hail garbage collection day
			this._size = 0;
		},
		
		removeIf: function(predicate)
		{
			if(!this._front)
				return;
				
			var i = this._front;
			do
			{
				if(predicate(i.data))	
					this._removeNode(i);
					
				i = i.next;
			} while(i);
		},
			
		findIf: function(predicate)
		{
			if(!this._front)
				return null;
				
			var i = this._front;
			do
			{
				if(predicate(i.data))
					return i.data;
			
				i = i.next;
			} while(i);
			
			return null;
		},
		
		_removeNode: function(node)
		{
			if(node == this._front)
				this.popFront();
			else if(node == this._back)
				this.popBack();
			else
			{
				if(node.previous)
					node.previous.next = node.next;
					
				if(node.next)
					node.next.previous = node.previous;
			}
		},
	};
	
	return List;
}();