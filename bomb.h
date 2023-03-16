#pragma once
#include "gameObject.h"

class bomb : public gameObject
{
private:
	ResourceManager* rm;
	VideoManager* vm;
	InputManager* im;

	const char* graphicPath = "assets/bombs.png";
	int graphicID;

	bool exploded = false;

	point position;

	float bombTime;
	float explodeTime = 2000;

public:
	bomb(int cellX, int cellY, int bombRange);
	~bomb();

	bool hasExploded()
	{
		return exploded;
	}

	point getPosition()
	{
		return position;
	}

	void update();
	void render();
};

