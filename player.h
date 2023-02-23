#pragma once
#include "gameObject.h"

enum Animation
{
	WALKING_DOWN,
	WALKING_UP,
	WALKING_LEFT,
	WALKING_RIGHT
};

class player : public gameObject
{
private:
	ResourceManager* rm;
	VideoManager* vm;
	InputManager * im;

	int speed = 4;

	Animation  currentAnimation = WALKING_DOWN;

	int frame = 0;
	float frameTime = 0;
	float eachTime = 150;

	bool idle = true;

	const char* graphicPath = "assets/player.png";
	int playerGraphicID;

	void renderAnimation(int frame);

public:
	player();
	~player();

	void update();
	void render();
};

