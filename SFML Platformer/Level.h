#pragma once

#include "stdafx.h"

#pragma region Block IDs

#define AIR Color(255, 255, 255)
#define GRASS Color(38, 127, 0)
#define DIRT Color(0, 0, 0)
#define PLAYER_START Color(255, 0, 0)

#pragma endregion

class Level {
	public:
		Level(string name);

		void Draw(RenderWindow & gameWindow);
		bool Collides(FloatRect source);
		Vector2f startLocation;

	private:
		void InitializeBlocks();

		string name;

		Texture grass, dirt;
		vector<DrawableGameObject*> blocks;
		Image level;
};

