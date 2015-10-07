'use strict';

/**
 * \brief Linked list data structure
 */
var List = function()
{
	/**
	 * \brief Constructor
	 */
	function List()
	{
	};

	/**
	 * \brief Internal node class constructor
	 * 
	 * \param Object data Data contained in  node.
	 * \param Node previous Previous node in list.
	 * \param Node next Next node in list.
	 */
	function Node(data, previous, next)
	{
		this.data = data;
		this.previous = previous || null;
		this.next = next || null;
	};

	List.prototype = 
	{
		_front: null, /**< Node Node in the back of the list */
		_back: null, /**< Node Node in the front of the list */
		_size: 0, /**< Number Number of nodes in the list */

		/**
		 * \brief Insert element to the end of the list.
		 * 
		 * \param Object data Data to insert.
		 */
		pushBack: function(data)
		{
			if(this._back)
				this._back = this._back.next = new Node(data, this._back, null);
			else
				this._front = this._back = new Node(data);
			
			this._size++;
		},

		/**
		 * \brief Insert element to the start of the list.
		 * 
		 * \param Object data Data to insert.
		 */
		pushFront: function(data)
		{
			if(this._front)
				this._front = this._front.previous = new Node(data, null, this._front);
			else
				this._front = this._back = new Node(data);
			
			this._size++;
		},

		/**
		 * \brief Remove element from end of the list.
		 */
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

		/**
		 * \brief Remove element from the start of the list.
		 */
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
		
		/**
		 * \brief Remove all elements from the list.
		 */
		clear: function()
		{
			this._front = this._back = null; // All hail garbage collection day
			this._size = 0;
		},
		
		/**
		 * \brief Remove an element if it matches the predicate function.
		 * 
		 * \param Function predicate Function that takes the element's data as parameter and returns a boolean value.
		 */
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
		
		/**
		 * \brief Find an element if it matches the predicate function.
		 * 
		 * \param Function predicate Function that takes the element's data as parameter and returns a boolean value. 
		 */
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
		
		/**
		 * \brief Remove node from list.
		 * 
		 * \param Node node Node to remove.
		 */
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