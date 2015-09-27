'use strict';

var SceneNode = function()
{
	function SceneNode()
	{
		GeometricObject.call(this);
		
		this._children = [];
		this._parent = null;
	}

	SceneNode.prototype =
	{		
		_children: null,
		_parent: null,
		
		update: function(dt)
		{
			this._updateCurrent(dt);
			this._updateChildren(dt);
		},
		
		render: function(ct, transform)
		{
			if(typeof transform === 'undefined')
				transform = this.getPosition();
			else
				transform = this.getPosition().addVector(transform);
			
			this._renderCurrent(ct, transform);
			this._renderChildren(ct, transform);
			
			// Debug
			this.drawGlobalBounds(ct, transform);
			this.drawMedians(ct, transform);
		},
		
		handleInput: function(dt)
		{
			this._handleInputCurrent(dt);
			this._handleInputChildren(dt);
		},

		getGlobalPosition: function()
		{
			if(this._parent)
				return this.getPosition().addVector(this._parent.getGlobalPosition());
			else
				return this.getPosition();
		},
		
		getGlobalBounds: function()
		{
			var position = this.getGlobalPosition();
			return new Rect(position.x, position.y, this._bounds.width, this._bounds.height);
		},
		
		drawGlobalBounds: function(ct, transform)
		{
			ct.lineWidth = 1;
			ct.strokeStyle = 'green';
			ct.strokeRect(transform.x, transform.y, this._bounds.width, this._bounds.height);
		},
		
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
		
		attachChild: function(sceneNode)
		{
			if(sceneNode._parent)
				sceneNode._parent.detachChild(sceneNode);
			
			sceneNode._parent = this;
			this._children.push(sceneNode);
		},
		
		detachChild: function(sceneNode)
		{
			var index = this._children.indexOf(sceneNode);
			if(index >= 0)
			{
				sceneNode._parent = null;
				this._children.splice(index, 1);
			}
		},
		
		
		_updateCurrent: function(dt)
		{
			
		},
		
		_renderCurrent: function(ct, transform)
		{
			
		},
		
		_handleInputCurrent: function(dt)
		{
			
		},
		
		
		_updateChildren: function(dt)
		{
			for(var i = 0; i < this._children.length; i++)
				this._children[i].update(dt);
		},
		
		_renderChildren: function(ct, transform)
		{
			for(var i = 0; i < this._children.length; i++)
				this._children[i].render(ct, transform);
		},
		
		_handleInputChildren: function(dt)
		{
			for(var i = 0; i < this._children.length; i++)
				this._children[i].handleInput(dt);
		},
	};
	
	$.extend(SceneNode.prototype, GeometricObject.prototype);

	return SceneNode;
}();
