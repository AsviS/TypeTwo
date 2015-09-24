'use strict';
var Input = function()
{	
	var my = {};
	
	
	var buffer1 =
	{
		pressedKeys: [],
		pressedButtons: [],
		textInput: '',
	};
	
	var buffer2 =
	{
		pressedKeys: [],
		pressedButtons: [],
		textInput: '',
	};
	
	var frontBuffer = buffer1;
	var backBuffer = buffer2;
	
	var downKeys = [];
	var downButtons = [];
	
	my.key = 
	{
		TAB: 		9,
		ENTER:		13,
		SHIFT:		16,
		CONTROL:	17,
		ALT:		18,
		LEFT:   	37,
		UP:     	38,
		RIGHT:  	39,
		DOWN:   	40,
		SPACE:  	32,
		A:      	65,
		S:      	83,
		D:      	68,
		W:      	87,
		ESC: 		27,
		BACKSPACE: 	8,
		
		
		isDown: function(keyCode) 
		{
			return downKeys[keyCode];
		},
		
		isPressed: function(key)
		{
			return frontBuffer.pressedKeys.indexOf(key) !== -1;
		},
	};
	
	my.mouse =
	{
		LEFT: 0,
		MIDDLE: 1,
		RIGHT: 2,
		position: new Vector(),
		
		isDown: function(button)
		{
			return downButtons[button];
		},
	
		isPressed: function(button)
		{
			return frontBuffer.pressedButtons.indexOf(button) !== -1;
		},
	};

	var onKeyDown = function(event)
	{
		backBuffer.pressedKeys.push(event.keyCode);
		downKeys[event.keyCode] = true;

		var key = event.keyCode;
		if(key === this.UP || key === this.DOWN || key === this.LEFT || key === this.RIGHT)
			return false;
		else
			return true;
	};
	
	var onKeyUp = function(event)
	{
		delete downKeys[event.keyCode];
	};
	
	var onTextInput = function(event)
	{
		backBuffer.textInput += String.fromCharCode(event.keyCode || event.charCode);
	};
	
	var onMouseDown = function(event)
	{
		backBuffer.pressedButtons.push(event.button);
		downButtons[event.button] = true;
		return true;
	};

	var onMouseUp = function(event)
	{
		delete downButtons[event.button];
		return true;
	};

	var updateMousePos = function(event, canvasId)
	{
		var absPos = utility.getAbsPos(canvasId);
		my.mouse.position = new Vector(event.pageX - absPos[0], event.pageY - absPos[1]);
	};

	my.bindInput = function(canvasId)
	{	
		$(window).keyup(onKeyUp);
		$(window).keydown(onKeyDown);
		$(window).keypress(onTextInput);
		
		$(document).on('contextmenu', function(e) 
		{
			if($(e.target).is("#" + canvasId))
				return false;
		});
		
		$(document)
			.on('mousedown', onMouseDown)
			.on('mouseup', onMouseUp)
			.on('mousemove', function(event) { updateMousePos(event, canvasId); });
		
			
		$(document).focus(function()
		{
			window.renderAll = true;
		});
	};
	
	my.swapEventBuffers = function()
	{	
		frontBuffer.pressedKeys.length = 0;
		frontBuffer.pressedButtons.length = 0;
		frontBuffer.textInput = '';
		
		if(frontBuffer == buffer1)
		{
			frontBuffer = buffer2;
			backBuffer = buffer1;
		}
		else
		{
			frontBuffer = buffer1;
			backBuffer = buffer2;
		}
	};
	
	my.getText = function()
	{
		return frontBuffer.textInput;
	};

	return my;
}();
