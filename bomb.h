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

	bool exploding = false;
	bool exploded = false;

	point position;

	rect leftBoom;
	rect rightBoom;
	rect topBoom;
	rect bottomBoom;

	float bombTime;
	float explodeTime = 2000;
	int range = 1;

public:
	bomb(int cellX, int cellY, int bombRange);
	~bomb();

	void generateExplosion();

	void update();
	void render();

	bool hasExploded()
	{
		return exploded;
	}

	point getPosition()
	{
		return position;
	}
};

