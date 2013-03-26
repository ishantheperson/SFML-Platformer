#include "stdafx.h"
#include "Game.h"

void Game::Start() {
	gameWindow.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_TITLE);
	gameWindow.clear();
	gameWindow.setFramerateLimit(MAX_FRAMERATE);
	gameWindow.setView(view);

	cout << "Player initialized at X: " << level.startLocation.x << " Y: " << level.startLocation.y << "\n";

	Loop();

	// disconnect

	// player.Disconnect();
}

void Game::Loop() {
	Event event;

	networkedPlayers = map<int, DrawableGameObject*>();

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

		// Draw NetworkedPlayers
		
		for (map<int, DrawableGameObject*>::iterator it = networkedPlayers.begin(); it != networkedPlayers.end(); it++) {
			cout << "INFO: Drawing networked player " << it -> first << endl;
			it -> second -> Draw(gameWindow);
			cout << "INFO: Done drawing networked player" << endl;
		}

		level.Draw(gameWindow);

		gameWindow.display();

	}
}

void Game::AddNetworkedPlayer(int id, DrawableGameObject* player) {
	cout << "INFO: Inserting new networked player..." << endl;
	// add player
	networkedPlayers.insert(map<int, DrawableGameObject*>::value_type(id, player));
	cout << "INFP: Successfully inserted new networked player" << endl;
}

void Game::UpdateNetworkedPlayer(int id, int x, int y) {
	cout << "INFO: Updating a networked player..." << endl;
	// update player
	cout << "INFO: Successfully updates a networked player" << endl;
}

void Game::Splash() { } // todo: implement splash screen

Player Game::player("player.png", Vector2f(25, 100), RIGHT);
RenderWindow Game::gameWindow;
vector<GameObject*> Game::gameObjects;

Level Game::level("scrolling.png");
View Game::view(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

map<int, DrawableGameObject*> Game::networkedPlayers;