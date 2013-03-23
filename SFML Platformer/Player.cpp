#include "stdafx.h"
#include "Player.h"


Player::Player(string name, Vector2f position, int direction) {
	cout << "INFO: Created new DrawableGameObject w/ normal constructor" << endl;
	if (!texture.loadFromFile("res/image/" + name)) {
		cout << "WARNING: could not load image " << name << endl;
	}
	cout << "INFO: Loaded image " << name << endl;
	this -> sprite.setTexture(texture);
	this -> sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	this -> sprite.setPosition(position);

	this -> direction = direction;
	loaded = true;
}

void Player::Update(Level world, View view) {
	#pragma region Movement
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		cout << "INFO: Player position X: " << sprite.getPosition().x << " Y: " << sprite.getPosition().y << endl;
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
}