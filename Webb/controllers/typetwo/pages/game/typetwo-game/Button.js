'use strict';
var Button = function()
{
	function Button(position, size, text, fontSize, callback, disabled)
	{

		this.x = position.x || 0;
		this.y = position.y || 0;
		this.width = size.x || 0;
		this.height = size.y || 0;
		this.bounds = new Rect(this.x, this.y, this.width, this.height);
		
		this.text = text || '';
		this.textPos = new Vector(this.x + this.width/2 - this.text.length * fontSize/4, this.y + this.height/2 - fontSize/2);
		this.callback = callback || function(){return false;};
		this.disabled = disabled === true ? true : false;
		
		if(this.disabled === true)
			this.disable();
		else
			this.enable();
	}

	$.extend(Button.prototype, GUIElement.prototype,
	{
		render: function(ct)
		{
			ct.beginPath();
			ct.rect(this.x, this.y, this.width, this.height);
			ct.fillStyle = this.color;
			ct.fill();
			ct.lineWidth = 5;
			ct.strokeStyle = this.borderColor;
			ct.stroke();	
			
			ct.fillStyle = this.textColor;
			ct.textBaseline = "top";
			ct.fillText(this.text, this.textPos.x, this.textPos.y);
		},
	
		select: function()
		{			
			if(this.isSelectable())
			{
				this.color = 'white';
				this.borderColor = 'gray';
				this.textColor = 'gray';
			}
		},
		
		deselect: function()
		{
			if(this.isSelectable())
			{
				this.color = 'gray';
				this.borderColor = 'silver';
				this.textColor = 'white';
			}
		},
		
		enable: function()
		{
			this.disabled = false;
			this.color = 'gray';
			this.borderColor = 'silver';
			this.textColor = 'white';
		},
		
		disable: function()
		{
			this.disabled = true;
			this.color = 'silver';
			this.borderColor = 'gray';
			this.textColor = 'gray';
		},
		
		isSelectable: function()
		{
			return this.disabled === false;
		},
		
		activate: function()
		{
			if(this.isSelectable())
			{
				this.callback();
			}
		}
	});
	
	return Button;
}();
