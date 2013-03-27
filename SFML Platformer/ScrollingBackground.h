#pragma once

class ScrollingBackground : public DrawableGameObject {
	public:
		ScrollingBackground(int speed, int offset);
		int speed;
		int offset;
};

