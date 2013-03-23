#pragma once

#include "stdafx.h"

using namespace sf;
using namespace std;

class GameObject
{
	public:
		GameObject(void);
		virtual ~GameObject(void);

		virtual void Draw(RenderWindow & window);
		virtual void Update();
};

