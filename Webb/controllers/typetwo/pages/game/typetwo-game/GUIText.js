'use strict';

/**
 * \brief Text container 
 */
var GUIText = function()
{
	/**
	 * \brief Constructor
	 * 
	 * \param Array text Text to show, formatted as an array of strings. Each element is one line.
	 * \param GUIText.FontSettings fontSettings Settings to use for font.
	 */
	function GUIText(text, fontSettings)
	{
		GUIElement.call(this);
		
		this._text = text;
		this.setFontSettings(fontSettings || new GUIText.FontSettings());
	}

	/**
	 * \brief Font settings constructor
	 * 
	 * \param String font Font style
	 * \param Number size Font size
	 * \param String emphasis Text emphasis (bold, italic etc.).
	 * \param String color CSS-compatible color string.
	 * \param String baseLine Text baseLine (top, middle, bottom, etc.).
	 */
	GUIText.FontSettings = function(font, size, emphasis, color, baseLine)
	{
		this.font = 		font 		|| this.font;
		this.size = 		size 		|| this.size;
		this.emphasis = 	emphasis 	|| this.emphasis;
		this.color = 		color 		|| this.color;
		this.baseLine = 	baseLine 	|| this.baseLine;
	};
	
	GUIText.FontSettings.prototype =
	{
		font: 'sans-serif', /**< String Font style */
		size: 20, /**< Number Font size */
		emphasis: null, /**< String Text emphasis (bold, italic etc.). */
		color: 'black', /**< String Text color. */
		baseLine: 'top', /**< String Text baseLine (top, middle, bottom, etc.). */
		
		/**
		 * \brief Convert this object into a Canvas-compatible font string.
		 * 
		 * \returns String Canvas-compatible font string.
		 */
		toCanvasFontString: function()
		{
			return (this.emphasis || '') + " " + this.size + "px " + this.font;
		}
	};


	$.extend(GUIText.prototype, GUIElement.prototype,
	{
		_text: 				undefined, /**< Array Text to show, formatted as an array of strings. Each element is one line. */
		_fontSettings: 		undefined, /**< GUIText.FontSettings Settings to use for font. */
		_canvasFontString: 	undefined, /**< Font settings formatted as Canvas-compatible font string. */
		_newlineStep: 		undefined, /**< Distance between two lines' baselines in pixels. */
		
		/**
		 * \brief Render this object
		 * 
		 * \param Canvas.context ct Canvas context to draw to.
		 * \param Rect transform Global transform.
		 */
		_renderCurrent: function(ct, transform)
		{
			ct.font = this._canvasFontString;
			ct.fillStyle = this._fontSettings.color;
			ct.textBaseline = this._fontSettings.baseLine;
			
			var yPos = transform.y;
			for(var i = 0; i < this._text.length; i++)
			{
				ct.fillText(this._text[i], transform.x, yPos);
				yPos += this._newlineStep;
			}
		},
		
		/**
		 * \brief Update bounding box size.
		 */
		_updateSize: function()
		{
			if(this._text.length > 0)
			{
				var width = config.canvas.context.measureText(this._text[0]).width;
				var height = this._fontSettings.size;
				
				if(this._text.length > 1)
				{
					for(var i = 1; i < this._text.length; i++)
					{
						var lineWidth = config.canvas.context.measureText(this._text[i]).width;
						if(lineWidth > width)
							width = lineWidth;
					}
					
					height += this._newlineStep * (this._text.length - 1);
				}
				
				this.setSize(width, height);	
			}
			else
				this.setSize(0, 0);	
		},
		
		/**
		 * \brief Set font settings.
		 * 
		 * \param GUIText.FontSettings fontSettings
		 */
		setFontSettings: function(fontSettings)
		{
			this._fontSettings = fontSettings;
			this._canvasFontString = fontSettings.toCanvasFontString();
			this._newlineStep = fontSettings.size * 1.2;
			
			config.canvas.context.font = this._canvasFontString;
			this._updateSize();		
		},
		
		/**
		 * \brief Set text color.
		 * 
		 * \param String color A CSS-compatible color string.
		 */
		setColor: function(color)
		{
			this._fontSettings.color = color;
		},
		
		/**
		 * \brief Set text.
		 * 
		 * \param Array text Text to show, formatted as an array of strings. Each element is one line.
		 */
		setText: function(text)
		{
			this._text = text || '';
			this._updateSize();
		},
		
	});

	return GUIText;
}();
