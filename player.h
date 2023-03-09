#pragma once
#include "gameObject.h"

#define COL_MARGIN 2

enum Animation
{
	WALKING_DOWN,
	WALKING_UP,
	WALKING_LEFT,
	WALKING_RIGHT
};

enum CollisionPoint
{
	TOP_LEFT, TOP_RIGHT,
	RIGHT_TOP, RIGHT_BOTTOM,
	BOTTOM_LEFT, BOTTOM_RIGHT,
	LEFT_TOP, LEFT_BOTTOM,
	ALL_POINTS
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

	// COLLISION POINTS
	vector<point> CollisionPoints;

	int lastX = -1;
	int lastY = -1;

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

