#include "stdafx.h"
#include "Level.h"

using namespace std;

// #define LEVEL_DEBUG

Level::Level(string name) {
	if (!(grass.loadFromFile("res/image/blocks/grass.png") && dirt.loadFromFile("res/image/blocks/dirt.png"))) {
		cout << "ERROR: Unable to load blocks" << "\n";
	}

	if (!level.loadFromFile("res/image/level/" + name)) {
		cout << "ERROR: Could not load level name " << name << "\n";
	}

	cout << "INFO: Loaded " << name << "\n";

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
#ifdef LEVEL_DEBUG
			cout << "INFO: Scanning block at X:" << x << " Y: " << y << "\n";
#endif
			if (pixel == AIR) {
#ifdef LEVEL_DEBUG
				cout << "INFO: Found air block at X:" << x << " Y: " << y << "\n";
#endif
				blocks.push_back(new DrawableGameObject);
				airAmount += 1;	
			}
			else if (pixel == GRASS) {
#ifdef LEVEL_DEBUG
				cout << "INFO: Found grass block at X:" << x << " Y: " << y << "\n";
#endif
				blocks.push_back(new DrawableGameObject(grass, new Vector2f(x * 100, y * 100)));
				grassAmount += 1;
			}
			else if (pixel == DIRT) {
#ifdef LEVEL_DEBUG
				cout << "INFO: Found dirt block at X:" << x << " Y: " << y << "\n";
#endif
				blocks.push_back(new DrawableGameObject(dirt, new Vector2f(x * 100, y * 100)));
				dirtAmount += 1;
			}
			else if (pixel == PLAYER_START) {
				blocks.push_back(new DrawableGameObject);
#ifdef LEVEL_DEBUG
				cout << "INFO: Found level start at X:" << x << " Y: " << y << "\n";
#endif
				startLocation = Vector2f(x * 100 + 50, y * 100 + 50);
			}
			else {
				blocks.push_back(new DrawableGameObject);
			}
		}
	}

#ifdef LEVEL_DEBUG
	cout << "INFO: Found " << grassAmount << " grass blocks" << "\n";
	cout << "INFO: Found " << dirtAmount << " dirt blocks" << "\n";
	cout << "INFO: Found " << airAmount << " air blocks" << "\n";
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