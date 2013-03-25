#include "stdafx.h"
#include "Level.h"

using namespace std;

Level::Level(string name) {
	if (!(grass.loadFromFile("res/image/blocks/grass.png") && dirt.loadFromFile("res/image/blocks/dirt.png"))) {
		Game::logger << "ERROR: Unable to load blocks" << "\n";
	}

	if (!level.loadFromFile("res/image/level/" + name)) {
		Game::logger << "ERROR: Could not load level name " << name << "\n";
	}

	Game::logger << "INFO: Loaded " << name << "\n";

	this -> name = name;

	InitializeBlocks();
}

void Level::InitializeBlocks() {
	unsigned int grassAmount = 0;
	unsigned int dirtAmount = 0;
	unsigned int airAmount = 0;

	for (unsigned int x = 0; x < level.getSize().x; x++) {
		for (unsigned int y = 0; y < level.getSize().y; y++) {
			Color pixel = level.getPixel(x, y);
#ifdef _DEBUG
			Game::logger << "INFO: Scanning block at X:" << x << " Y: " << y << "\n";
#endif
			if (pixel == AIR) {
#ifdef _DEBUG
				Game::logger << "INFO: Found air block at X:" << x << " Y: " << y << "\n";
#endif
				blocks.push_back(new DrawableGameObject);
				airAmount += 1;	
			}
			else if (pixel == GRASS) {
#ifdef _DEBUG
				Game::logger << "INFO: Found grass block at X:" << x << " Y: " << y << "\n";
#endif
				blocks.push_back(new DrawableGameObject(grass, new Vector2f(x * 100, y * 100)));
				grassAmount += 1;
			}
			else if (pixel == DIRT) {
#ifdef _DEBUG
				Game::logger << "INFO: Found dirt block at X:" << x << " Y: " << y << "\n";
#endif
				blocks.push_back(new DrawableGameObject(dirt, new Vector2f(x * 100, y * 100)));
				dirtAmount += 1;
			}
			else if (pixel == PLAYER_START) {
				blocks.push_back(new DrawableGameObject);
#ifdef _DEBUG
				Game::logger << "INFO: Found level start at X:" << x << " Y: " << y << "\n";
#endif
				startLocation = Vector2f(x * 100 + 50, y * 100 + 50);
			}
			else {
				blocks.push_back(new DrawableGameObject);
			}
		}
	}

#ifdef _DEBUG
	Game::logger << "INFO: Found " << grassAmount << " grass blocks" << "\n";
	Game::logger << "INFO: Found " << dirtAmount << " dirt blocks" << "\n";
	Game::logger << "INFO: Found " << airAmount << " air blocks" << "\n";
#endif
}

void Level::Draw(RenderWindow & window) {
	for (vector<DrawableGameObject*>::iterator i = blocks.begin(); i != blocks.end(); ++i) {
		(*i) -> Draw(window);
	}
}

bool Level::Collides(FloatRect source) {
	// TODO: iterator over blocks
	for (vector<DrawableGameObject*>::iterator i = blocks.begin(); i != blocks.end(); ++i) {
		if (((*i) -> loaded) == true) {
			if ((*i) -> sprite.getGlobalBounds().intersects(source)) {
				return true; 
			} 
		}
	}

	return false;
}