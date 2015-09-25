'use strict';

var GUIText = function()
{
	function GUIText(text, position, fontSettings)
	{
		this._text = text;
		this.position = position || this.position;		
		this.setFontSettings(fontSettings || GUIText.FontSettings.prototype);
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
		size: '10',
		emphasis: null,
		color: 'black',
		baseLine: 'top',
		
		toCanvasFontString: function()
		{
			return this.emphasis + " " + this.size + "px " + this.font;
		}
	};


	$.extend(GUIText.prototype, GUIElement.prototype,
	{
		_text: [],
		position: new Vector(),
		_fontSettings: null,
		_canvasFontString: '',
		_newlineStep: 0,
		
		render: function(ct)
		{
			ct.font = this._canvasFontString;
			ct.fillStyle = this._fontSettings.color;
			ct.textBaseline = this._fontSettings.baseLine;
			
			var yPos = this.position.y;
			for(var i = 0; i < this._text.length; i++)
			{
				ct.fillText(this._text[i], this.position.x, yPos);
				yPos += this._newlineStep;
			}
		},
		
		setFontSettings: function(fontSettings)
		{
			this._fontSettings = fontSettings;
			this._canvasFontString = fontSettings.toCanvasFontString();
			this._newlineStep = fontSettings.size * 3;
		},
	});

	return GUIText;
}();
