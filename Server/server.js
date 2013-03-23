/// <reference path="./nodelib/node.js">
var dgram = require('dgram');
var server = dgram.createSocket('udp4');

console.log("Socket created\n");

var players = []; // players;

server.on("message", function (message, information) {
    console.log("Got Message: " + message.toString());
});

server.bind(9000);