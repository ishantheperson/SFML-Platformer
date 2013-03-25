// SFML Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>

#define PORT 9000

void Listen(sf::UdpSocket &);

struct Player {
	float x, y;
	std::string name;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<Player> players;
	int index = 0;

	sf::UdpSocket socket;
	socket.bind(PORT);

	while (true) {
		Listen(socket);
	}

	return 0;
}

void Listen(sf::UdpSocket & socket) {
	socket.bind(PORT);
	char data[1024];
	std::size_t received = 0;
	sf::IpAddress sender;
	unsigned short port;
	socket.receive(data, sizeof(data), received, sender, port);

	std::cout << "Message received: " << sender.toString() << " said " << data << std::endl;

	// respond
	std::string message = "received message";
	socket.send(message.c_str(), message.size() + 1, sender, port);
}