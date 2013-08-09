#include <map>

#include "stdafx.h"
#include "Game.h"

void Game::Start() {
	gameWindow.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_TITLE);
	gameWindow.clear();
	gameWindow.setFramerateLimit(MAX_FRAMERATE);
	gameWindow.setView(view);

	cout << "Player initialized at X: " << level.startLocation.x << " Y: " << level.startLocation.y << "\n";

	NetworkedPlayers* networkedPlayers = new NetworkedPlayers;
	
	Loop();

	// disconnect

	// player.Disconnect();
}

void Game::Loop() {
	Event event; // this isn't really necessary but SFML says use it

	while (gameWindow.isOpen()) {
		while (gameWindow.pollEvent(event)) {
			// handle events BEFORE drawing for an unlaggy gameplay experience !
			switch (event.type) {
				case Event::EventType::Closed:
					gameWindow.close();
					break;

				case Event::EventType::LostFocus:
					IsFocused = false; break;

				case Event::EventType::GainedFocus:
					IsFocused = true; break;
			}
		}
		gameWindow.clear();
		gameWindow.setView(view); // i actually made this work

		if (IsFocused) {
			player.Update(level, view);
		}
		player.Draw(gameWindow);

		// Update and Draw GameObjects
		for (unsigned int i = 0; i < gameObjects.size(); i++) {
			if (IsFocused) {
				gameObjects[i] -> Update();
			}
			gameObjects[i] -> Draw(gameWindow);
		}

		// Draw NetworkedPlayers
		
		for (map<int, DrawableGameObject>::iterator it = networkedPlayers.begin(); it != networkedPlayers.end(); it++) {
			(it ->second).Draw(gameWindow);
		}

		level.Draw(gameWindow);

		gameWindow.display();

	}
}

void Game::AddNetworkedPlayer(int id, DrawableGameObject player) {
	cout << "INFO: Inserting new networked player..." << endl;
	// add player
	networkedPlayers[id] = player;
	cout << "INFP: Successfully inserted new networked player" << endl;
}

void Game::UpdateNetworkedPlayer(int id, int x, int y) {
	cout << "INFO: Updating a networked player..." << endl;
	// update player
	networkedPlayers[id].sprite.setPosition(x, y);
	cout << "INFO: Successfully updates a networked player" << endl;
}

void Game::Splash() { } // todo: implement splash screen

Player Game::player("player.png", Vector2f(25, 100), RIGHT);
RenderWindow Game::gameWindow;
vector<GameObject*> Game::gameObjects;

Level Game::level("scrolling.png");
View Game::view(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

NetworkedPlayers* Game::networkedPlayers;

bool Game::IsFocused;