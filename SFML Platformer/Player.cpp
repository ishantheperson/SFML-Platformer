#include "stdafx.h"
#include "Player.h"

#define GRAVITY 5
#define JUMP_HEIGHT 20
#define SPEED 2

#define PORT 9000 // this must be the same
#define LISTEN_PORT 9001 // this can change
#define ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1024

Player::Player(string name, Vector2f position, int direction) {
	#pragma region Sprite
	Sprite sprite;
	cout  << "INFO: Created new DrawableGameObject w/ normal constructor" << "\n";
	if (!texture.loadFromFile("res/image/" + name)) {
		cout  << "WARNING: could not load image " << name << "\n";
	}
	cout  << "INFO: Loaded image " << name << "\n";
	this -> sprite.setTexture(texture);
	this -> sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	this -> sprite.setPosition(position);

	this -> direction = direction;
	loaded = true;

	this -> lastPosition = position;

	#pragma endregion

	#pragma region Network
	address = new IpAddress(ADDRESS);
	this -> socket.setBlocking(true);
	socket.bind(Socket::AnyPort); // pick a port, any port

	Packet packet;

	string command = "join " + to_string(sprite.getPosition().x) + " " + to_string(sprite.getPosition().y);

	packet.append(command.c_str(), command.size());
	socket.send(packet, *address, PORT);

	char response[BUFFER_SIZE];
	size_t received = 0;
	unsigned short port;

	IpAddress sender;

	cout  << "INFO: Receiving message..." << "\n";
	socket.receive(response, 1024, received, sender, port);
	cout  << "INFO: Received message." << "\n";

	string message(response, received);
	cout  << "INFO: Player received message: " << message << "\n";
	id = atoi(message.c_str());

	// after initial connection do not block
	
	// socket.setBlocking(false);

	#pragma endregion
}

Player::~Player() {
	delete address; // remove pointer
}

void Player::Update(Level world, View view) {
	#pragma region Movement
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		cout  << "INFO: Player position X: " << sprite.getPosition().x << " Y: " << sprite.getPosition().y << "\n";
	}

	bool left = Keyboard::isKeyPressed(Keyboard::A);
	bool right = Keyboard::isKeyPressed(Keyboard::D);
	bool up = Keyboard::isKeyPressed(Keyboard::W);

	FloatRect collisionRect(sprite.getGlobalBounds());
	collisionRect.height -= 2; // feet;

	FloatRect rightCollisionRect(collisionRect);
	rightCollisionRect.width /= 2;
	rightCollisionRect.left += 50;

	FloatRect leftCollisionRect(collisionRect);
	leftCollisionRect.width /= 2;

	FloatRect groundCollisionRect(collisionRect);
	groundCollisionRect.top += groundCollisionRect.height - 2;
	groundCollisionRect.height = 2;
	groundCollisionRect.width -= 10;
	groundCollisionRect.left += 5;
	
	if (right && !(world.Collides(rightCollisionRect))) {
		if (direction == LEFT) {
			Flip(); 
			direction = RIGHT;
		}
		if (sprite.getPosition().x - (view.getCenter().x + (WINDOW_WIDTH / 2)) >= -200) {
			Game::view.move(SPEED, 0);
		}
		sprite.move(SPEED, 0); 
	}
	
	if (left && !(world.Collides(leftCollisionRect))) {
		if (direction == RIGHT) {
			Flip();
			direction = LEFT;
		}
		if (sprite.getPosition().x - (view.getCenter().x - (WINDOW_WIDTH / 2)) <= 100) {
			Game::view.move(-SPEED, 0);	
		}
		sprite.move(-SPEED, 0);
	}

	bool grounded = false;

	// gravity
	sprite.move(0, GRAVITY);
	if (world.Collides(sprite.getGlobalBounds())) { // on ground
		sprite.move(0, -GRAVITY);
		grounded = true;
		velocity = 0;
	}

	if (grounded) {
		if (up) {
			velocity += JUMP_HEIGHT;
		}
	}
	else {
		if (world.Collides(groundCollisionRect) == false) {
			velocity -= 1;
		}
	}

	for (int i = 1; i <= velocity; i++) {
		sprite.move(0, -1);
		if (world.Collides(groundCollisionRect)) { // collides
			sprite.move(0, 1);
			velocity = 0;
		}
	}
	#pragma endregion
	#pragma region Network
	// send data to server
	if (lastPosition != sprite.getPosition()) {
		socket.setBlocking(false);
		cout  << "Sending data..." << "\n";
		Packet packet;
		string command = "move " + to_string(id) + " " + to_string(sprite.getPosition().x) + " " + to_string(sprite.getPosition().y);
		packet.append(command.c_str(), command.size());

		socket.send(packet, *address, PORT);

		cout  << "Data sent" << "\n";
	} // else no data needs to be sent

	#pragma endregion

	lastPosition = sprite.getPosition();
}

void Player::Listen() {
	char data[BUFFER_SIZE]; // received data
	size_t received = 0; // amount we received
	unsigned short port; // the port it was received from

	IpAddress sender; // the person who sent the data
	socket.receive(data, BUFFER_SIZE, received, sender, port); // receive the data

	string message(data, received);
}


#ifdef _DEBUG
ostream& operator<< (ostream& stream, const Player& player) {
	stream << player.sprite.getPosition().x << ' ' << player.sprite.getPosition().y;
	return stream;
}
#endif