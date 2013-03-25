#pragma once

#include "stdafx.h" 
#include "GameObject.h"
#include "DrawableGameObject.h"
#include "Level.h"
#include "Player.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
#define WINDOW_TITLE "The Amazing Platformer Game"

#define MAX_FRAMERATE 60

using namespace sf;
using namespace std;

class Game {
	public:
		static void Start();
		static void AddDrawableGameObject(DrawableGameObject object);

		static vector<GameObject*> gameObjects;
		static Player player;
		static View view;

		static ofstream Game::logger;

	private:
		static void Loop();
		static void Splash();
		static RenderWindow gameWindow;
		static Level level;
};

