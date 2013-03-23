#include "stdafx.h"
#include "DrawableGameObject.h"

using namespace std;

DrawableGameObject::DrawableGameObject() {
	cout << "INFO: Created new DrawableGameObject w/ Default Constructor" << endl;
	this -> loaded = false;
}

DrawableGameObject::DrawableGameObject(string name, Vector2f position = Vector2f(0, 0), int direction = 1)
{
	cout << "INFO: Created new DrawableGameObject w/ normal constructor" << endl;
	if (!texture.loadFromFile("res/image/" + name)) {
		cout << "WARNING: could not load image " << name << endl;
	}
	cout << "INFO: Loaded image " << name << endl;
	sprite.setTexture(texture);
	sprite.setPosition(position);

	this -> direction = direction;
	loaded = true;
}

DrawableGameObject::DrawableGameObject(Texture & texture, Vector2f* position) {
	cout << "INFO: Created new DrawableGameObject with Block Constructor" << endl;
	this -> texture = texture;	
	sprite.setTexture(texture);
	sprite.setPosition(position -> x, position -> y);
	
	loaded = true;
}

DrawableGameObject::~DrawableGameObject(void) {
	cout << "Destructor called on DrawableGameObject " << endl;
}

void DrawableGameObject::Update() { }

void DrawableGameObject::Draw(RenderWindow & window) {
	if (loaded) {
		window.draw(sprite);
	}
}

void DrawableGameObject::Flip() {
	sprite.setScale(sprite.getScale().x * -1, 1);
}