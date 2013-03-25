#include "stdafx.h"
#include "Fade.h"

Fade::Fade(int time, Color color, RenderWindow* window)
{
	// constructer values
	this -> time = time;
	this -> color = color;
	this -> window = window;

	Texture texture;
	if (!texture.loadFromFile("/res/image/pixel.png")) {
		cout  << "WARNING: Couldn't load pixel!" << "\n";
	}
	pixel.setTexture(texture);
}

void Fade::Draw(RenderWindow* window) { }
void Fade::Update() { }