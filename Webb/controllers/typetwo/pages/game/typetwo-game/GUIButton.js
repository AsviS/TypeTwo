'use strict';

/**
 * \brief Button for GUI
 */
var GUIButton = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Rect bounds Position and size of button.
	 * \param String text Text shown in the middle of the button
	 * \param Function callback Function to call when button is pressed.
	 * \param Boolean disabled Flag indicating whether the callback function should be called when button is pressed.
	 */
	function GUIButton(bounds, text, callback, disabled)
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

	$.extend(GUIButton.prototype, GUIElement.prototype,
	{
		_text: undefined, /**< String Text shown in the middle of the button. */
		
		/**
		 * \brief Render this object
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
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
	
		/**
		 * \brief Select this element
		 */
		select: function()
		{			
			if(this.isSelectable())
			{
				this.color = this.isActivated() ? 'silver' : 'white';
				this.borderColor = 'gray';
				this._text.setColor('gray');
			}
			
		},
		
		/**
		 * \brief Deselect this element.
		 */
		deselect: function()
		{
			if(this.isSelectable())
			{
				this.color = 'gray';
				this.borderColor = 'silver';
				this._text.setColor('white');
			}
		},
		
		/**
		 * \brief Enable the user to activate this button.
		 */
		enable: function()
		{
			this.disabled = false;
			this.color = 'gray';
			this.borderColor = 'silver';
			this._text.setColor('white');
		},
		
		/**
		 * \brief Prevent the user from activating this button.
		 */
		disable: function()
		{
			this.disabled = true;
			this.color = 'silver';
			this.borderColor = 'gray';
			this._text.setColor('gray');
		},
		
		/**
		 * \brief Button is selectable if enabled.
		 */
		isSelectable: function()
		{
			return this.disabled === false;
		},
		
		/**
		 * \brief Activate button's callback function.
		 */
		activate: function()
		{
			this.color = 'silver';
			if(this.isSelectable())
				this._isActivated = true;
		},
		
		/**
		 * \brief Deactivate this element.
		 */
		deactivate: function()
		{
			this._isActivated = false;
		},
		
		/**
		 * \brief Handle device input for this node
		 * 
		 * \param Number dt Time per frame
		 */
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
	
	return GUIButton;
}();
