#pragma once
#include "gameObject.h"

class player : public gameObject
{
private:
	ResourceManager* rm;
	VideoManager* vm;
	InputManager * im;

	const char* graphicPath = "assets/player.png";
	int playerGraphicID;

public:
	player();
	~player();

	void update();
	void render();
};

