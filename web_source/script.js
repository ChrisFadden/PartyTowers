// This is where we define our messages (similar to an enum)
var MSG_LOGIN = 999;

$(document).ready(function() {

    $("#game").hide();

   // Setup our message objects (packets)
    setupMessages();

    $("#room").val("");

    $("#back").click(function() {
        $("#towers").hide();
        $("#buttons").show();
    });

    $("#room").on('input', function() {
        $("#room").val($("#room").val().toUpperCase());
    });

    $("#login").click(function() {
        startConnection();
            });

    // This interval can be used for anything, but it currently only handles incoming messaged.
    setInterval(gameLoop, 15);
});

function setupMessages() {
    // Incoming MSG_LOGIN
    var m1 = createMsgStruct(MSG_LOGIN, false);
    m1.addChars(2);
    // This packet will be carrying two chars
    
    var m3 = createMsgStruct(3, false);
    m3.addChars(1);

    var m4 = createMsgStruct(4, false);
    m4.addChars(1);

    var m5 = createMsgStruct(5, false);
    m5.addString();

    // Outgoing MSG_LOGIN
    var i1 = createMsgStruct(MSG_LOGIN, true);
    // This packet sends a string (our name) to the server
    i1.addChars(4);

    var i2 = createMsgStruct(2, true);
    i2.addChars(1);

    var i3 = createMsgStruct(3, true);

    var i4 = createMsgStruct(4, true);
    i4.addChars(2);
}

function startConnection() {
    // This will be called when the connection is successful
    var onopen = function() {
        // We ask for a new packet for type MSG_LOGIN
        var packet = newPacket(MSG_LOGIN);
        packet.write($("#room").val());
        // and then we send the packet!
        packet.send();
        $("#login").hide();
        $("#room").hide();

        $("#notify").text("Connected!");
        $("#game").show();
        $("#towers").hide();
    }

    // This will be called when the connection is closed
    var onclose = function() {
        window.location.href = '/';
    }

    $("#upBtn").on("click", function() {
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
    $("#placeBtn").click(function() {
        var packet = newPacket(3);
        packet.send();
    });

    $(".buyBtn").click(function() {
        var packet = newPacket(4);
        var val = $(this).data("num");
        packet.write(val);
        packet.send();
        $("#back").click();
    });

    // Start the connection!
    $("#notify").text("Connecting...");
    wsconnect("ws://localhost:8886", onopen, onclose);
}

function begin() {
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
        $("#notify").text("You are client number " + pid);
    } else if (msgID === 3) {
        var t = packet.read();
        if (t == "1") {
            $("#buttons").hide();
            $("#towers").show();
        } else {
            $("#notify").text("Cannot place here.");
        }
    } else if (msgID === 4) {
        var t = packet.read();
        if (t === "1") {
            $("#notify").text("Tower placed!");
        } else {
            $("#notify").text("Could not place tower.");
        }
    } else if (msgID === 5) {
        var money = packet.read();
        $("#money").text("Points: "+money);
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
