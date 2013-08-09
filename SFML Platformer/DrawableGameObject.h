#pragma once

#include "stdafx.h"

#define LEFT 0
#define RIGHT 1

using namespace sf;
using namespace std;

class DrawableGameObject : public GameObject {
	public:
		DrawableGameObject(); // default constructor
		DrawableGameObject(string filePath, Vector2f position, int direction); 
		DrawableGameObject(Texture & texture, Vector2f* position);
		virtual ~DrawableGameObject(void);

		virtual void Draw(RenderWindow & window);
		virtual void Update();

		void Flip();
		void SetPosition(float x, float y);

		Sprite sprite;
		bool loaded;

	protected:
		Image image;
		Texture texture;
		IntRect oldFlipRect;
		int direction; // 0 = left, 1 = right
};

