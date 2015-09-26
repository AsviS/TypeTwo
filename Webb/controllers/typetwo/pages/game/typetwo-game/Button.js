'use strict';
var Button = function()
{
	function Button(bounds, text, callback, disabled)
	{
		GUIElement.call(this);
		
		this.setBounds(bounds);

		this._text = new GUIText(text);
		var guiTextBounds = this._text.getBounds();
	
		this._text.setOrigin(guiTextBounds.width / 2, guiTextBounds.height / 2);
		this._text.setPosition(this._bounds.width / 2, this._bounds.height / 2);

		this.attachChild(this._text);
		
		this.callback = callback || function(){return false;};
		this.disabled = disabled === true ? true : false;
		
		if(this.disabled === true)
			this.disable();
		else
			this.enable();
			
		this.deselect();
	}

	$.extend(Button.prototype, GUIElement.prototype,
	{
		_text: undefined,
		
		_renderCurrent: function(ct, transform)
		{
			ct.beginPath();
			ct.rect(transform.x, transform.y, this._bounds.width, this._bounds.height);
			ct.fillStyle = this.color;
			ct.fill();
			ct.lineWidth = 5;
			ct.strokeStyle = this.borderColor;
			ct.stroke();	
		},
	
		select: function()
		{			
			if(this.isSelectable())
			{
				this.color = this.isActivated() ? 'silver' : 'white';
				this.borderColor = 'gray';
				this._text.setColor('gray');
			}
			
		},
		
		deselect: function()
		{
			if(this.isSelectable())
			{
				this.color = 'gray';
				this.borderColor = 'silver';
				this._text.setColor('white');
			}
		},
		
		enable: function()
		{
			this.disabled = false;
			this.color = 'gray';
			this.borderColor = 'silver';
			this._text.setColor('white');
		},
		
		disable: function()
		{
			this.disabled = true;
			this.color = 'silver';
			this.borderColor = 'gray';
			this._text.setColor('gray');
		},
		
		isSelectable: function()
		{
			return this.disabled === false;
		},
		
		activate: function()
		{
			this.color = 'silver';
			if(this.isSelectable())
				this._isActivated = true;
		},
		
		deactivate: function()
		{
			this._isActivated = false;
		},
		
		_handleInputCurrent: function()
		{
			if(this.isActivated())
			{
				if(!Input.mouse.isDown(Input.mouse.LEFT))
				{
					this.deactivate();
					
					if(this.getGlobalBounds().containsPoint(Input.mouse.position.x, Input.mouse.position.y))
					{
						this.select();
						this.callback();
					}
						
				}
			}
		},
	});
	
	return Button;
}();
