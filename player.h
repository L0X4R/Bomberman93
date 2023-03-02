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

	const char* graphicPath = "assets/player.png";
	int playerGraphicID;

	int speed = 4;

	int frame = 0;
	float frameTime = 0;
	float eachTime = 150;
	Animation  currentAnimation = WALKING_DOWN;
	bool idle = true;

	vector<vector<int>>* levelReference;
	int stageToCheck = -1;

	int cellPosX = -1;
	int cellPosY = -1;
	int lastPosX = -1;
	int lastPosY = -1;

	objRect collision;

	vector<vector<int>> availableCollisions =
	{
		// STAGE 1
		vector<int> {0},

		// STAGE 2
		vector<int> {2, 5, 10, 11, 12, 13, 18, 21, 26, 29, 34, 37, 42, 43, 44, 45}
	};

	void renderAnimation(int frame);

public:
	player();
	~player();

	void update();
	void render();

	void setLevelRefrence(int stage, vector<vector<int>>* ref)
	{
		stageToCheck = stage;
		levelReference = ref;
	}
};

