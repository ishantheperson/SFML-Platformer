#pragma once

#include "stdafx.h"
#include "GameObject.h"

using namespace sf;

class Fade : public GameObject
{
	public:	
		Fade(int time, Color color, RenderWindow* window);

		void Update();
		void Draw(RenderWindow* window);

	private:
		int time;
		Color color;

		RenderWindow* window;

		Sprite pixel;
};

