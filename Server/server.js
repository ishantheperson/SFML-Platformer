/// <reference path="./nodelib/node.js">

var port = 9000;

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

console.log("Socket created\n");

function Player(x, y, ip, port) {
    this.x = x || 0;
    this.y = y || 0;

    this.ip = ip;
    this.port = port;
}

var players = []; // connected players

server.on("message", function (messageText, information) {
    var params = messageText.toString().split(" ");

    switch (params[0]) { // 0th term is command
        case "join":
            var currentPlayer = new Player(parseInt(params[1]), parseInt(params[2]), information.address, information.port);

            players.push(currentPlayer);

            var message = players.indexOf(currentPlayer).toString(10);
            var response = createBuffer(message);

            server.send(response, 0, response.length, information.port, information.address, function (error, sent) {
                if (error) {
                    console.log("ERROR: could not send login response");
                }
                else {
                    console.log("SUCCESS: sent login data to " + information.address + ":" + information.port);
                }
            });

            //broadcast mesage to others
            var broadcastMessage = "joined " + message + " " + currentPlayer.x + " " + currentPlayer.y;
            var broadcastBuffer = new Buffer(broadcastMessage.length);
            broadcastBuffer.write(broadcastMessage);

            players.forEach(function (player, index, array) {
                if (player.ip != currentPlayer.ip && player.port != currentPlayer.port) {
                    server.send(broadcastBuffer, 0, broadcastBuffer.length, player.port, player.ip, function () {
                        // succes
                        console.log("SUCCESS: Sent move data to player " + index);
                    });
                }
            });
            break;

        case "move":
            var id = parseInt(params[1], 10);

            var x = parseInt(params[2], 10);
            var y = parseInt(params[3], 10);

            players[id].x = x;
            players[id].y = y;

            console.log("INFO: Data received from player " + id + " move to " + x + " " + y);

            break;

        case "disconnect":

            break;

        default:
            console.log("WARNING: Cannot handle message " + message.toString() + " from " + information.address);
            break;
    }
});

function createBuffer(text) {
    var buffer = new Buffer(text.length);
    buffer.write(text);

    return buffer;
}

server.bind(port);
console.log("Server listening on port " + port);
