#pragma once

#include "stdafx.h"
#include "DrawableGameObject.h"
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class Player : public DrawableGameObject
{
	public:
		Player (string name, Vector2f position, int direction);
		virtual ~Player();
		void Update(Level level, View view);

		friend ostream& operator<<(ostream& stream, const Player& player);
	private:
		void Listen();

		float velocity;
		Vector2f lastPosition;

		Thread listenThread;
		IpAddress* address;
		UdpSocket socket;
		Packet packet;
		int id;
};

