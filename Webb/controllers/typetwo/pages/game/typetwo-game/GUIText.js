'use strict';

var GUIText = function()
{
	function GUIText(text, position, lineGapThickness)
	{
		this._text = text;
		this._position = position;
		this._lineGapThickness = lineGapThickness;
	}


	$.extend(GUIText.prototype, GUIElement.prototype,
	{
		_text: [],
		_position: new Vector(),
		_lineGapThickness: 0,
		
		render: function(ct)
		{
			ct.save();
			var yPos = this._position.y;
			ct.fillStyle = 'black';
			for(var i = 0; i < this._text.length; i++)
			{
				ct.fillText(this._text[i], this._position.x, yPos);
				yPos += this._lineGapThickness;
			}
			ct.restore();
		},
	});

	return GUIText;
}();
