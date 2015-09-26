// This is where we define our messages (similar to an enum)
var MSG_LOGIN = 999;

$(document).ready(function() {

    $("#game").hide();

   // Setup our message objects (packets)
    setupMessages();

    $("#room").val("EPXX");

    $("#room").on('input', function() {
        $("#room").val($("#room").val().toUpperCase());
    });

    $("#login").click(function() {
        startConnection();
        $("#login").hide();
        $("#room").hide();
        $("#notify").text("Connecting...");
    });

    // This interval can be used for anything, but it currently only handles incoming messaged.
    setInterval(gameLoop, 15);
});

function setupMessages() {
    // Incoming MSG_LOGIN
    var m1 = createMsgStruct(MSG_LOGIN, false);
    m1.addChars(2);
    // This packet will be carrying two chars

    // Outgoing MSG_LOGIN
    var i1 = createMsgStruct(MSG_LOGIN, true);
    // This packet sends a string (our name) to the server
    i1.addChars(4);

    var i2 = createMsgStruct(2, true);
    i2.addChars(1);
}

function startConnection() {
    // This will be called when the connection is successful
    var onopen = function() {
        // We ask for a new packet for type MSG_LOGIN
        var packet = newPacket(MSG_LOGIN);
        packet.write($("#room").val());
        // and then we send the packet!
        packet.send();
        $("#notify").text("Connected!");
        $("#game").show();
    }

    // This will be called when the connection is closed
    var onclose = function() {
        window.location.href = '/';
    }

    $("#upBtn").click(function() {
        var packet = newPacket(2);
        packet.write("u");
        packet.send();
    });
    $("#downBtn").click(function() {
        var packet = newPacket(2);
        packet.write("d");
        packet.send();
    });
    $("#leftBtn").click(function() {
        var packet = newPacket(2);
        packet.write("l");
        packet.send();
    });
    $("#rightBtn").click(function() {
        var packet = newPacket(2);
        packet.write("r");
        packet.send();
    });
    // Start the connection!
    wsconnect("ws://128.61.27.41:8886", onopen, onclose);
}

// This function handles incoming packets
function handleNetwork() {
    // First we check if we have enough data
    // to handle a full packet
    if (!canHandleMsg()) {
        return;
    }

    // Read the packet in
    var packet = readPacket();

    // Find out what type of packet it is
    msgID = packet.msgID;

    // And handle it!
    if (msgID === MSG_LOGIN) {
        var pid = packet.read();
        alert("You are client number " + pid);
    }
}

// This is called every 15 millis, and is currently used to
// handle incoming messaged. This can do more.
function gameLoop() {
    handleNetwork();
}

// Does a simple httpGet request. Not used in this example.
function httpGet(url, callback, carryout) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", url, true);
	xmlHttp.onreadystatechange = function() {
		if (xmlHttp.readyState == 4) {
			if (xmlHttp.status == 200) {
				alert(xmlHttp.responseText);
			}
		}
	}
	xmlHttp.send();
}
