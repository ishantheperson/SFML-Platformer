/// <reference path="./nodelib/node.js">

var port = 9000;

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

console.log("Socket created\n");

function Player(x, y, ip, port) { // player object
    this.x = x;
    this.y = y;

    this.ip = ip;
    this.port = port;
}

var players = []; // connected players

server.on("message", function (message, information) {
    var params = message.toString().split(" ");

    switch (params[0]) { // 0th term is command
        case "join": // alerts server that a player has joined
            var currentPlayer = new Player(parseInt(params[1]), parseInt(params[2]), information.address, information.port); // params[1] is current X, 2 is current Y, address is sender IP

            players.push(currentPlayer); // add it to array

            var response = players.indexOf(currentPlayer).toString(10); // get ID
            var buffer = new Buffer(response.length); // create buffer
            buffer.write(response); // add message to buffer

            server.send(buffer, 0, buffer.length, information.port, information.address, function (error, sent) { // send player his ID
                if (error) { // oh noes something blew up
                    console.log("ERROR: could not send login response");
                }
                else { // its k
                    console.log("SUCCESS: sent login data to " + information.address + ":" + information.port);
                }
            });

            // broadcast mesage to others
            response = "joined" + response + " " + currentPlayer.x + " " + currentPlayer.y; // message previously contained ID
                                                                                            // format: "joined <ID> <X> <Y>

            // prepare data to be sent to everyone else
            buffer = new Buffer(message.length); // clear out the old buffer with a new one
            buffer.write(message);

            players.forEach(function (player, index, array) {
                if (player.ip != information.address && player.port != information.port) { // is not the person who just joined (they dont have same IP or port)
                    server.send(buffer, 0, buffer.length, player.port, player.ip); // send message
                }
            });
            break;

        case "move": // updates server's knowledge of player position
            var id = parseInt(params[1], 10); // get player ID

            var x = parseInt(params[2], 10); // get move X
            var y = parseInt(params[3], 10); // get move Y

            players[id].x = x; // set player X
            players[id].y = y; // set player Y

            // tell us that the server got some data
            console.log("INFO: Data received from player " + id + " move to " + x + " " + y);

            // prepare data to be sent
            var response = id + " " + x + " " + y;
            var buffer = new Buffer(response.length);
            buffer.write(response);

            players.forEach(function (player, index, array) {
                if (player.ip != information.ip && player.port != information.port) { // not player who just sent this message
                    server.send(buffer, 0, buffer.length, player.port, player.ip)
                }
            });

            break;

        case "disconnect": // player disconnected, remove them from players[] array
            var id = parseInt(params[1], 10); // get player ID from args
            players.splice(id, 1); // remove player

            // inform everyone else that a player just disconnected

            break;

        default: // unknown command
            console.log("WARNING: Cannot handle message " + message.toString() + " from " + information.address); 
            break;
    }
});

server.bind(port);
console.log("Server listening on port " + port);