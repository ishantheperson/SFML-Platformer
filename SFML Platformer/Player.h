#pragma once

#include "stdafx.h"
#include "DrawableGameObject.h"

using namespace std;
using namespace sf;

#define GRAVITY 5
#define JUMP_HEIGHT 20
#define SPEED 2

class Player : public DrawableGameObject
{
	public:
		Player (string name, Vector2f position, int direction);

		void Update(Level level, View view);
	private:
		float velocity;
};

