/// <reference path="./nodelib/node.js">

// Game Server by Ishan Bhargava for SFML Platformer
var port = 9000;

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

console.log("Socket created\n");

function Player(x, y, ip, port, id) {
    this.id = id;
    this.x = x;
    this.y = y;

    this.ip = ip;
    this.port = port;
}

var players = []; // connected players

server.on("message", function (messageText, information) {
    var params = messageText.toString().split(" ");

    switch (params[0]) { // 0th term is command
        case "join":
            var currentPlayer = new Player(parseInt(params[1]), parseInt(params[2]), information.address, information.port, 0);

            players.push(currentPlayer);
            var id = players.indexOf(currentPlayer);
            currentPlayer.id = id;

            console.log("Joined player: " + currentPlayer.id + " from " + currentPlayer.ip + ":" + currentPlayer.port);

            var message = id.toString(10);
            var response = createBuffer(message);

            // SERVER RESPONSE: sends ID
            server.send(response, 0, response.length, information.port, information.address, function (error, sent) { 
                if (error) {
                    console.log("ERROR: could not send login response");
                }
                else {
                    console.log("SUCCESS: sent login data to " + information.address + ":" + information.port);
                }
            });


            // send back other players
            players.forEach(function (player, index, array) {
                if (player.id != id) {
                    // SERVER RESPONSE: sends player COMMAND to ADD NEW PlAYER (VERB == ADD)
                    // SYNTAX: add <ID> <X> <Y>
                    var buffer = createBuffer("add " + player.id + " " + player.x + " " + player.y);
                    console.log("INFO: Sending message " + buffer.toString());
                    server.send(buffer, 0, buffer.length, information.port, information.address);
                }
            });

            // broadcast mesage to others
            // SERVER RESPONSE: sends player COMMAND to ADD NEW CONNECTED PLAYER (VERB == JOINED)
            // SYNTAX: joined <ID> <X> <Y>
            var broadcastMessage = "joined " + message + " " + currentPlayer.x + " " + currentPlayer.y;
            var broadcastBuffer = createBuffer(broadcastMessage);

            players.forEach(function (player, index, array) {
                if (player.id != id) {
                    server.send(broadcastBuffer, 0, broadcastBuffer.length, player.port, player.ip, function (error, sent) {
                        // succes
                        if (!error) { console.log("SUCCESS: Sent join data to player " + index); }
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


            // SEVER COMMAND MOVE
            // syntax: move <id> <x> <y>
            var message = "move " + id + " " + x + " " + y;
            var buffer = new Buffer(message.length);
            buffer.write(message);

            players.forEach(function (player, index, array) {
                if (player.id != id) {
                    server.send(buffer, 0, buffer.length, player.port, player.ip, function(error, sent) {
                        if (!error) { console.log("SUCCESS: Sent move data to player " + player.id + " at " + player.ip + ":" + player.port); }
                    });
                }
            });

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

console.log("Game Server listening on port " + port);

// web server to configure the server with web-based interface

var http = require('http');

var webServer = http.createServer(function (request, response) {
    if (request.url == "/home") {
        // home page
        response.writeHead(200, "text/html");

        response.write("<html><head><title>Node.js Game Server Management</title></head>");
        response.write("<style type=\"text/css\">body { margin: 50px 100px; font-family: Arial; } p { margin-left: 5px; } </style>");
        response.write("<body>");
        response.write("<h1>Connected Players</h1>");
        players.forEach(function (player, index, array) {
            response.write("<p><b>Player " + player.id + "</b><br>");
            response.write("IP Address: " + player.ip + ":" + player.port + "<br>");
            response.write("Position: (" + player.x + ", " + player.y + ")<br></p>");
        });
        response.write("</body></html>");

        response.end();
    }
});
webServer.listen(10985);