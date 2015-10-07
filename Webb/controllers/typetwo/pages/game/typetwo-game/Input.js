'use strict';

/**
 * \brief Device input module.
 * 
 * Keeps check on currently pressed keys and mouse buttons.
 * Holds an event buffer holding keys and mouse buttons that
 * have been pressed.
 */
var Input = function()
{	
	var my = {};
	
	
	var buffer1 =
	{
		pressedKeys: [], /**< Array Key pressed events. */
		pressedButtons: [], /**< Array Mouse button pressed events. */
		textInput: '', /**< String User text input */
	}; /**< Array */
	
	var buffer2 =
	{
		pressedKeys: [], /**< Array Key pressed events. */
		pressedButtons: [], /**< Array Mouse button pressed events. */
		textInput: '', /**< String User text input */
	}; /**< Array */
	
	var frontBuffer = buffer1; /**< Array Front buffer shown to the outside */
	var backBuffer = buffer2; /**< Array Back buffer used to stored incoming input events */
	
	var downKeys = []; /**< Currently pressed down keys. */
	var downButtons = []; /**< Currently pressed down mouse buttons */
	
	/**
	 * \brief Keycodes and key-related functions
	 */
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
		PARAGRAPH: 	0,
		
		/**
		 * \brief Is this key currently pressed?
		 * 
		 * \param Number keyCode Keycode of key to check.
		 * \returns Boolean/undefined True if pressed. False or undefined if not.
		 */
		isDown: function(keyCode) 
		{
			return downKeys[keyCode];
		},
		
		/**
		 * \brief Has this key been pressed in the latest front buffer?
		 * 
		 * \param Number key Keycode of key to check.
		 * \returns Boolean True if pressed, else false.
		 */
		isPressed: function(key)
		{
			return frontBuffer.pressedKeys.indexOf(key) !== -1;
		},
	};
	
	/**
	 * \brief Mouse button keycodes and button-related functions.
	 */
	my.mouse =
	{
		LEFT: 0,
		MIDDLE: 1,
		RIGHT: 2,
		TAP: 3,
		position: new Vector(), /**< Vector Current mouse position */
		
		/**
		 * \brief Is this button currently pressed?
		 * 
		 * \param Number button Keycode of button to check.
		 * \returns Boolean/undefined True if pressed. False or undefined if not.
		 */
		isDown: function(button)
		{
			return downButtons[button];
		},
	
		/**
		 * \brief Has this key been pressed in the latest front buffer?
		 * 
		 * \param Number button Keycode of button to check.
		 * \returns Boolean True if pressed, else false.
		 */
		isPressed: function(button)
		{
			return frontBuffer.pressedButtons.indexOf(button) !== -1;
		},
	};

	/**
	 * \brief On key down event.
	 * 
	 * \param Event event
	 * 
	 * \returns Boolean
	 */
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
	
	/**
	 * \brief On key up event.
	 * 
	 * \param Event event
	 */
	var onKeyUp = function(event)
	{
		downKeys[event.keyCode] = false;
	};
	
	/**
	 * \brief On text input event
	 * 
	 * \param Event event
	 */
	var onTextInput = function(event)
	{
		backBuffer.textInput += String.fromCharCode(event.keyCode || event.charCode);
	};
	
	/**
	 * \brief On mouse button down event.
	 * 
	 * \param Event event
	 * 
	 * \returns Boolean
	 */
	var onMouseDown = function(event)
	{
		backBuffer.pressedButtons.push(event.button);
		downButtons[event.button] = true;
		return true;
	};

	/**
	 * \brief On mouse button up event.
	 * 
	 * \param Event event
	 * 
	 * \returns Boolean
	 */
	var onMouseUp = function(event)
	{
		downButtons[event.button] = false;
		return true;
	};

	/**
	 * \brief On mouse move event
	 * 
	 * \param Event event
	 */
	var updateMousePos = function(event, canvasId)
	{
		var absPos = utility.getAbsPos(canvasId);
		my.mouse.position = new Vector(event.pageX - absPos[0], event.pageY - absPos[1]);
	};
	
	/**
	 * \brief On tap event.
	 * 
	 * \param Event event
	 */
	var onTap = function(event, canvasId)
	{
		backBuffer.pressedButtons.push(my.mouse.TAP);
		updateMousePos({pageX: event.originalEvent.touches[0].pageX, pageY: event.originalEvent.touches[0].pageY}, canvasId);
	};

	/**
	 * \brief Bind input checking to a HTML5 Canvas element.
	 * 
	 * \param String ID of Canvas element
	 */
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
		$(document).on('touchstart', function(event){onTap(event, canvasId);});


		$(document).focus(function()
		{
			window.renderAll = true;
		});
	};
	
	/**
	 * \brief Swap event buffers.
	 * 
	 * Should be done before checking input
	 */
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
	
	/**
	 * \brief Get text input from front buffer.
	 * 
	 * \returns String User text input
	 */
	my.getText = function()
	{
		return frontBuffer.textInput;
	};

	return my;
}();
