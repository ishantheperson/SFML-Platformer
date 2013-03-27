#include "stdafx.h"
#include "DrawableGameObject.h"

using namespace std;

DrawableGameObject::DrawableGameObject() {
	this -> loaded = false;
}

DrawableGameObject::DrawableGameObject(string name, Vector2f position = Vector2f(0, 0), int direction = 1) {
	if (!image.loadFromFile("res/image/" + name)) {
		cout << "WARNING: could not load image " << name << endl;
	}

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(position);

	this -> direction = direction;
	loaded = true;
}

DrawableGameObject::DrawableGameObject(Texture & texture, Vector2f* position) {
	this -> texture = texture;	
	sprite.setTexture(texture);
	sprite.setPosition(position -> x, position -> y);
	
	loaded = true;
}

DrawableGameObject::~DrawableGameObject(void) { }

void DrawableGameObject::Update() { }

void DrawableGameObject::Draw(RenderWindow & window) {
	if (loaded) {
		window.draw(sprite);
	}
}

void DrawableGameObject::Flip() {
	// sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);	
	image.flipHorizontally();

	texture.loadFromImage(image);
}