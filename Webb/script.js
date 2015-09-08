window.onload = function(){

	var label1 = document.getElementById("label1");
	var buttonSend = document.getElementById("sendButton");
	var textfield = document.getElementById("textbox");

	var socket = new WebSocket("ws://192.168.0.191:8080", "order");

	socket.onopen = function (event){
		label1.innerHTML ="Uppkopplad!";
	}

	socket.onclose = function(event){
		label1.innerHTML = "Butiken är stängd.";
	}

	socket.onmessage = function (event) {
		if (typeof event.data === "string"){
			label1.innerHTML = event.data;
		};
	}

	buttonSend.onclick = function (event) {
		sendMessage();
	}

	textfield.onkeypress = function (event) {
		if(event.keyCode == 13){
			sendMessage();
		};
	}

	function sendMessage (event){
		if (socket.readyState == WebSocket.OPEN) {
			socket.send(textfield.value);
			textfield.value = "";
		};
	}

}