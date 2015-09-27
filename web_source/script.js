// This is where we define our messages (similar to an enum)
var MSG_LOGIN = 999;

var pID = 0;

$(document).ready(function() {

    $("#game").hide();

   // Setup our message objects (packets)
    setupMessages();

    $("#room").val("");

    $(".back").click(function() {
        $("#towers").hide();
        $("#upgrade").hide();
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

    var m6 = createMsgStruct(6, false);
    m6.addChars(1);

    // Outgoing MSG_LOGIN
    var i1 = createMsgStruct(MSG_LOGIN, true);
    // This packet sends a string (our name) to the server
    i1.addChars(4);

    var i2 = createMsgStruct(2, true);
    i2.addChars(2);
    i2.addChars(1);

    var i3 = createMsgStruct(3, true);
    i3.addChars(2);

    var i4 = createMsgStruct(4, true);
    i4.addChars(2);
    i4.addChars(2);

    var i6 = createMsgStruct(6, true);
    i6.addChars(2);

    var i10 = createMsgStruct(10, true);
    i10.addChars(2);
    i10.addString();
}

function startConnection() {
    // This will be called when the connection is successful
    var onopen = function() {
        // We ask for a new packet for type MSG_LOGIN
        var packet = newPacket(MSG_LOGIN);
        packet.write($("#room").val());
        // and then we send the packet!
        packet.send();
        
    }

    // This will be called when the connection is closed
    var onclose = function() {
        window.location.href = '/';
    }

    $("#upBtn").on("click", function() {
        var packet = newPacket(2);
        packet.write(pID);
        packet.write("u");
        packet.send();
    });
    $("#downBtn").click(function() {
        var packet = newPacket(2);
        packet.write(pID);
        packet.write("d");
        packet.send();
    });
    $("#leftBtn").click(function() {
        var packet = newPacket(2);
        packet.write(pID);
        packet.write("l");
        packet.send();
    });
    $("#rightBtn").click(function() {
        var packet = newPacket(2);
        packet.write(pID);
        packet.write("r");
        packet.send();
    });
    $("#placeBtn").click(function() {
        var packet = newPacket(3);
        packet.write(pID);
        packet.send();
    });

    $(".buyBtn").click(function() {
        var packet = newPacket(4);
        packet.write(pID);
        var val = $(this).data("num");
        packet.write(val);
        packet.send();
        $(".back").click();
    });

    $(".upgradeBtn").click(function() {
        var packet = newPacket(6);
        packet.write(pID);
        packet.send();
        $(".back").click();
    });

    // Start the connection!
    $("#notify").text("Connecting...");
    wsconnect("ws://128.61.27.41:8886", onopen, onclose);
    //wsconnect("ws://localhost:8886", onopen, onclose);
}

function begin() {

    var packet = newPacket(10);
    var name = $("#name").val();
    packet.write(pID);
    packet.write(name);
    packet.send();

    $(".login").hide();
    $("#login").hide();
    $("#room").hide();

    $("#notify").text("Connected!");
    $("#game").show();
    $("#towers").hide();
    $("#upgrade").hide();
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
        pID = packet.read();
        $("#notify").text("You are client number " + pID);
        begin();
    } else if (msgID === 3) {
        var t = packet.read();
        if (t == "1") {
            $("#buttons").hide();
            $("#towers").show();
            $(".tower").show();
            $("#notify").text("Select a tower.");
        } else if (t == "0"){
            $("#notify").text("Cannot place here.");
        } else {
            $("#buttons").hide();
            $("#upgrade").show();
            $(".tower").hide();
            $("*[data-num="+t+"]").show();
            $("#notify").text("Upgrade your tower.");
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
        $("#notify2").text("Currency: "+money);
    } else if (msgID === 6) {
        var succ = packet.read();
        if (succ === "1") {
            $("#notify").text("Tower upgraded!");
        } else {
            $("#notify").text("Could not upgrade tower.");
        }
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
