'use strict';

/**
 * \brief An updatable, renderable node that can handle events.
 * 
 * A node has one parent node and may have several children nodes.
 * Any update, render or input handling invoked on this node 
 * also calls its children's update, render and input handling functions.
 */
var SceneNode = function()
{
	/**
	 * \brief Constructor
	 */
	function SceneNode()
	{
		GeometricObject.call(this);
		
		this._children = new List();
		this._parent = null;
	}

	SceneNode.prototype =
	{		
		_children: null, /**< List SceneNode objects that are children to this node */
		_parent: null, /**< SceneNode Parent node to this node. */
		
		/**
		 * \brief Update this node and its children
		 * 
		 * \param Number dt Time per frame
		 */
		update: function(dt)
		{
			this._updateCurrent(dt);
			this._updateChildren(dt);
		},
		
		/**
		 * \brief Render this node and its children
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
		render: function(ct, transform)
		{
			if(typeof transform === 'undefined')
				transform = this.getPosition();
			else
				transform = this.getPosition().addVector(transform);
			
			this._renderCurrent(ct, transform);
			this._renderChildren(ct, transform);
		},
		
		/**
		 * \brief Handle device input for this node and its children
		 * 
		 * \param Number dt Time per frame
		 */
		handleInput: function(dt)
		{
			this._handleInputCurrent(dt);
			this._handleInputChildren(dt);
		},

		/**
		 * \brief Get global position of this node.
		 * 
		 * Each SceneNode's position is relative to its parent's
		 * position. For example, if this node's parent has no parent,
		 * and is positioned at (10, 10), and this node is positioned at
		 * (5, 0), this function will return (15, 10).
		 * 
		 * \returns Vector Global position of this node.
		 */
		getGlobalPosition: function()
		{
			if(this._parent)
				return this.getPosition().addVector(this._parent.getGlobalPosition());
			else
				return this.getPosition();
		},
		
		/**
		 * \brief Get global bounding box of this node.
		 * 
		 * \seealso SceneNode.prototype.getGlobalPosition
		 * \returns Rect Global bounding box of this node.
		 */
		getGlobalBounds: function()
		{
			var position = this.getGlobalPosition();
			return new Rect(position.x, position.y, this._bounds.width, this._bounds.height);
		},
		
		/**
		 * \brief Draw global bounding box.
		 * 
		 *  Used mainly for debugging purposes.
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
		drawGlobalBounds: function(ct, transform)
		{
			ct.lineWidth = 1;
			ct.strokeStyle = 'green';
			ct.strokeRect(transform.x, transform.y, this._bounds.width, this._bounds.height);
		},
		
		/**
		 * \brief Draw this node's global bounding box's medians.
		 * 
		 * Used mainly for debugging purposes.
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
		drawMedians: function(ct, transform)
		{
			ct.lineWidth = 1;
			ct.strokeStyle = 'green';
			
			ct.beginPath();
			
			ct.moveTo(transform.x + this._bounds.width / 2, transform.y);
			ct.lineTo(transform.x + this._bounds.width / 2, transform.y + this._bounds.height);
			
			ct.moveTo(transform.x, transform.y + this._bounds.height / 2);
			ct.lineTo(transform.x + this._bounds.width, transform.y + this._bounds.height / 2);

			ct.closePath();
			ct.stroke();
		},
		
		/**
		 * \brief Snap this node's position in relation to parent.
		 * 
		 * "Float" in this context has the same meaning as CSS's float.
		 * 
		 * \param String whereX Where to snap on X-axis (center, left, right)
		 * \param String whereY Where to snap on Y-axis (center, top, bottom)
		 */
		floatTo: function(whereX, whereY)
		{
			if(!this._parent)
				return;

			this.setOrigin(0, 0);
			switch(whereX)
			{
				case 'center':
					this.setPositionX((this._parent._bounds.width - this._bounds.width) / 2);
					break;
				
				case 'left':
					this.setPositionX(0);
					break;
					
				case 'right':
					this.setPositionX(this._parent._bounds.width - this._bounds.width);
					break;
					
				default:
					break;
			}
			
			switch(whereY)
			{
				case 'center':
					this.setPositionY((this._parent._bounds.height - this._bounds.height) / 2);
					break;
				
				case 'top':
					this.setPositionY(0);
					break;
					
				case 'bottom':
					this.setPositionY(this._parent._bounds.height - this._bounds.height);
					break;
					
				default:
					break;
			}
		},
		
		/**
		 * \brief Attach a SceneNode to this node.
		 * 
		 * Sets the specified node's parent to this node.
		 * 
		 * \param SceneNode sceneNode Node to attach to this node.
		 */
		attachChild: function(sceneNode)
		{
			if(sceneNode._parent)
				sceneNode._parent.detachChild(sceneNode);
			
			sceneNode._parent = this;
			this._children.pushBack(sceneNode);
		},
		
		/**
		 * \brief Detach child from this node.
		 * 
		 * \param SceneNode sceneNode Node to detach from this node.
		 */
		detachChild: function(sceneNode)
		{
			this._children.remove(sceneNode);
		},
		
		/**
		 * \brief Update this node
		 * 
		 * \param Number dt Time per frame
		 */
		_updateCurrent: function(dt)
		{
			
		},
		
		/**
		 * \brief Render this node
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
		_renderCurrent: function(ct, transform)
		{
			
		},
		
		
		/**
		 * \brief Handle device input for this node
		 * 
		 * \param Number dt Time per frame
		 */
		_handleInputCurrent: function(dt)
		{
			
		},
		
		/**
		 * \brief Update this node's children
		 * 
		 * \param Number dt Time per frame
		 */
		_updateChildren: function(dt)
		{
			for(var i = this._children.begin(); i != this._children.end(); i = i.next)
				i.data.update(dt);
		},
		
		/**
		 * \brief Render this node's children
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
		_renderChildren: function(ct, transform)
		{
			for(var i = this._children.begin(); i != this._children.end(); i = i.next)
				i.data.render(ct, transform);
		},
		
		/**
		 * \brief Handle device input for this node's children
		 * 
		 * \param Number dt Time per frame
		 */
		_handleInputChildren: function(dt)
		{
			for(var i = this._children.begin(); i != this._children.end(); i = i.next)
				i.data.handleInput(dt);
		},
	};
	
	$.extend(SceneNode.prototype, GeometricObject.prototype);

	return SceneNode;
}();
