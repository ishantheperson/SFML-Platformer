#include "stdafx.h"
#include "Game.h"

void Game::Start() {
	gameWindow.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_TITLE);
	gameWindow.clear();
	gameWindow.setFramerateLimit(MAX_FRAMERATE);
	gameWindow.setView(view);

	cout << "Player initialized at X: " << level.startLocation.x << " Y: " << level.startLocation.y << endl;

	Loop();
}

void Game::Loop() {
	Event event;

	while (gameWindow.isOpen()) {
		while (gameWindow.pollEvent(event)) {
			// handle events BEFORE drawing
			if (event.type == Event::EventType::Closed) {
				gameWindow.close();
			}
		}
		gameWindow.clear();
		gameWindow.setView(view);

		player.Update(level, view);

		player.Draw(gameWindow);

		// Update and Draw GameObjects
		for (unsigned int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i] -> Update();
			gameObjects[i] -> Draw(gameWindow);
		}

		level.Draw(gameWindow);

		gameWindow.display();

	}
}

void Game::Splash() { }

Player Game::player("player.png", Vector2f(25, 100), RIGHT);
RenderWindow Game::gameWindow;
vector<GameObject*> Game::gameObjects;

Level Game::level("scrolling.png");
View Game::view(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));