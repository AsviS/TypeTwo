window.onload = function(){

	var label1 = document.getElementById("label1");
	var buttonSend = document.getElementById("sendButton");
	var buttonConn = document.getElementById("connectButton");
	var textbox = document.getElementById("textbox");
	var username = document.getElementById("namefield");
	var ipfield;
	var portfield;

	buttonConn.onclick = function (event){
		joinRoom();	
	}

	username.onkeypress = function (event) {
		if(event.keyCode == 13){
			joinRoom();
		};
	}

	buttonSend.onclick = function (event) {
		sendMessage();
	}
}

function joinRoom(){
	ipfield = document.getElementById("ipfield");
	portfield = document.getElementById("portfield");
	username = document.getElementById("namefield");
	socket = new WebSocket('ws://' + ipfield.value + ':' + portfield.value, "order");
	addMessage("Connecting..");

	socket.onopen = function (event){
		//addMessage("Uppkopplad!");
		socket.send(username.value + " connected!");
		textbox.focus();
	}

	socket.onclose = function (event){
		addMessage("Connection closed.");
	}

	socket.onmessage = function (event) {
		if (typeof event.data === "string"){
			addMessage(event.data);
		};
	}

	textbox.onkeypress = function (event) {
		if(event.keyCode == 13){
			sendMessage();
		};
	}
}

function addMessage (mess){
	label1.innerHTML += mess + "<br />";

	var chatWin = document.getElementById("chat-window");
	chatWin.scrollTop = chatWin.scrollHeight;
}

function sendMessage (event){
	if (socket.readyState == WebSocket.OPEN) {
		socket.send(username.value + ": " + textbox.value);
		textbox.value = '';
	}
	else{
		alert("Not connected");
	}
}