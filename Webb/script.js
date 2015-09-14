// Main
window.onload = function(){

	var buttonSend = document.getElementById("sendButton");
	var buttonConn = document.getElementById("connectButton");
	var textbox = document.getElementById("textbox");

	buttonConn.onclick = function (event){
		joinRoom();	
	}

	document.getElementById("passfield").onkeypress = function (event) {
		if(event.keyCode == 13){
			joinRoom();
		};
	}

	buttonSend.onclick = function (event) {
		sendMessage();
	}

	setInterval(checkColor(), 1000);

}

function checkColor(){
	document.getElementById("colorText").style.color = document.getElementById("textColor").value;
}

function joinRoom(){
		socket = new WebSocket('ws://' + document.getElementById("ipfield").value + ':' + 
			document.getElementById("portfield").value + "/" + 
			document.getElementById("namefield").value + "/" + 
			document.getElementById("passfield").value, "chat");
		addMessage("Connecting..");

	socket.onopen = function (event){
		textbox.focus();
		document.getElementById("connectButton").innerHTML="Disconnect";
		document.getElementById("connectButton").value="Disconnect";
	}

	socket.onclose = function (event){
		addMessage("Connection closed.");
		document.getElementById("connectButton").innerHTML="Connect";
		document.getElementById("connectButton").value="Connect";
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

	document.getElementById("label1").innerHTML += mess + "<br />";

	var text = "This is text";
	var textArr = text.split("is");

	var chatWin = document.getElementById("chat-window");
	chatWin.scrollTop = chatWin.scrollHeight;
}

function sendMessage (event){
	if (socket.readyState == WebSocket.OPEN) {
		var message = textbox.value;
		socket.send(message);
		textbox.value = '';
	}
	else{
		alert("Not connected");
	}
}