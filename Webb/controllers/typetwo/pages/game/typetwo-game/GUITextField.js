'use strict';

/**
 * \brief Text input field where the user can enter text.
 */
var GUITextField = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Rect bounds Bounding box of field.
	 * \param Function submitCallback Function to call when the user presses the enter key while the field is activated.
	 * \param Boolean isHidden Should the text input shown in the field be masked (password field)?
	 */
	function GUITextField(bounds, submitCallback, isHidden)
	{
		GUIElement.call(this);
		
		this.setBounds(bounds);

		this._submitCallback = submitCallback || this._submitCallback;
		this._isHidden = (isHidden === true || isHidden === false) ? isHidden : this._isHidden;
		this._text = '';
	}


	$.extend(GUITextField.prototype, GUIElement.prototype,
	{	
		_text: null, /**< String Text inputted into the field. */
		_submitCallback: function(){}, /**< Function Function to call when the user pressed the enter key while the field is activated. */
		_isHidden: false, /**< Boolean If true, the input is masked with asterisks. */
		_textMask: '', /**< String Mask to render instead of text if _isHidden is true. */
		
		/**
		 * \brief Render this object
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
		_renderCurrent: function(ct, transform)
		{			
			ct.fillStyle = 'white';
			ct.fillRect(transform.x, transform.y, this._bounds.width, this._bounds.height);
			
			if(this._text.length > 0)
			{
				ct.fillStyle = 'black';
				ct.textBaseline = "middle";
				if(this._isHidden)
					ct.fillText(new Array(this._text.length + 1).join("*"), transform.x + ct.lineWidth * 5, transform.y + this._bounds.height / 2);
				else
					ct.fillText(this._text, transform.x + ct.lineWidth * 5, transform.y + this._bounds.height / 2);
			}

			if(this._isActivated)
			{
				ct.strokeStyle = 'black';
				ct.strokeRect(transform.x, transform.y, this._bounds.width, this._bounds.height);
			}
			else if(this._isSelected)
			{
				ct.strokeStyle = 'gray';
				ct.strokeRect(transform.x, transform.y, this._bounds.width, this._bounds.height);
			}
				
		},
		
		/**
		 * \brief Handle device input for this node
		 * 
		 * \param Number dt Time per frame
		 */
		_handleInputCurrent: function()
		{
			this._text += Input.getText().replace(/[\n\t\r]+/g, '');

			if(Input.key.isPressed(Input.key.ENTER))
				this._submitCallback();
				
			
			if(this._text.length > 0 && Input.key.isPressed(Input.key.BACKSPACE))
			{
				if(Input.key.isDown(Input.key.CONTROL))
					this._text = '';
				else
					this._text = this._text.substr(0, this._text.length - 2);
			}
		},
		
		/**
		 * \brief Is this element selectable?
		 * 
		 * \returns Boolean True if selectable, else false.
		 */
		isSelectable: function()
		{
			return true;
		},
		
		
		/**
		 * \brief Activate this element
		 */
		activate: function()
		{
			this._isActivated = true;
            $('#field').trigger('focus');
		},
		
		/**
		 * \brief Deactivate this element
		 */
		deactivate: function()
		{
			this._isActivated = false;
            $('#field').trigger('blur');
		},
		
		/**
		 * \brief Get text in field
		 * 
		 * \returns String Text in field.
		 */
		getText: function()
		{
			return this._text;
		}
	});


	return GUITextField;
}();
