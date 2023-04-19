#pragma once
#include "gameObject.h"

enum powerType
{
	PlusBomb, RemoteControl, PlusRadius, PlusSpeed, PlusLives, PlusScore,
	PowerQuantity
};

class powerUp : public gameObject
{
private:
	// MANAGERS
	ResourceManager* rm;
	VideoManager* vm;

	// GRAPHICS
	const char* graphicPath = "assets/power_ups.png";
	int graphicID;

	rect Camera;

	// POWER UP CONFIG
	int type;
	float liveTime = 8000;

	int BombToAdd = 1;
	int RadiusToAdd = 1;
	int SpeedToAdd = 1;
	int LivesToAdd = 1;
	int ScoreToAdd = 5000;

public:
	powerUp(int posX, int posY, int genPowerType);
	~powerUp();

	void update();
	void render();

	float remainingTime()
	{
		return liveTime;
	}

	int getType()
	{
		return type;
	}

	void setCamera(int X = 0, int Y = 0)
	{
		Camera.x = X;
		Camera.y = Y;
	}
};

