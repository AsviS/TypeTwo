'use strict';

var GUIText = function()
{
	function GUIText(text, fontSettings)
	{
		GUIElement.call(this);
		
		this._text = text;
		this.setFontSettings(fontSettings || new GUIText.FontSettings());
	}

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
		font: 'sans-serif',
		size: 20,
		emphasis: null,
		color: 'black',
		baseLine: 'top',
		
		toCanvasFontString: function()
		{
			return (this.emphasis || '') + " " + this.size + "px " + this.font;
		}
	};


	$.extend(GUIText.prototype, GUIElement.prototype,
	{
		_text: 				undefined,
		_fontSettings: 		undefined,
		_canvasFontString: 	undefined,
		_newlineStep: 		undefined,
		
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
		
		setFontSettings: function(fontSettings)
		{
			this._fontSettings = fontSettings;
			this._canvasFontString = fontSettings.toCanvasFontString();
			this._newlineStep = fontSettings.size * 1.2;
			
			config.canvas.context.font = this._canvasFontString;
			this._updateSize();		
		},
		
		setColor: function(color)
		{
			this._fontSettings.color = color;
		},
		
		setText: function(text)
		{
			this._text = text || '';
			this._updateSize();
		},
		
	});

	return GUIText;
}();
