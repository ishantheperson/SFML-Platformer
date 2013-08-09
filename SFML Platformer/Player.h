#pragma once

#include "stdafx.h"
#include "DrawableGameObject.h"

#include <SFML/Network.hpp>
#include <thread>
#include <boost/algorithm/string.hpp>


using namespace std;
using namespace sf;

class Player : public DrawableGameObject
{
	public:
		Player (string name, Vector2f position, int direction);
		virtual ~Player();

		void Update(Level& level, View& view);
		void Disconnect();

		friend ostream& operator<<(ostream& stream, const Player& player);
	private:
		static void Listen();
		string GetRandomName();

		float velocity;
		Vector2f lastPosition;

		thread* listenThread;

		IpAddress* address;
		static UdpSocket* socket;
		Packet packet;

		int id;
		string serverMessage;
		Text serverMessageText;
		string name;
};

