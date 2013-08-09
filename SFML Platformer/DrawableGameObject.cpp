#include "stdafx.h"
#include "DrawableGameObject.h"

using namespace std;

DrawableGameObject::DrawableGameObject() {
	this -> loaded = false;
}

DrawableGameObject::DrawableGameObject(string name, Vector2f position = Vector2f(0, 0), int direction = 1) {
	if (!image.loadFromFile("res/image/" + name)) {
		cout  << "WARNING: could not load image " << name << "\n";
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
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.scale(-1, 1);
}

void DrawableGameObject::SetPosition(float x, float y) {
	sprite.setPosition(x, y);
}