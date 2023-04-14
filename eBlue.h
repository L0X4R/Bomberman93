#pragma once
#include "gameObject.h"
#include "mapLevel.h"

class eBlue : public gameObject
{
	enum CollisionPoint
	{
		TOP_LEFT, TOP_RIGHT,
		RIGHT_TOP, RIGHT_BOTTOM,
		BOTTOM_LEFT, BOTTOM_RIGHT,
		LEFT_TOP, LEFT_BOTTOM,
		ALL_POINTS
	};

	enum DIR_MOVE
	{
		UP, DOWN,
		LEFT, RIGHT,
		ALL_DIRS
	};

private:
	// MANAGERS
	ResourceManager* rm;
	VideoManager* vm;

	// GRAPHICS
	const char* graphicPath = "assets/enemy_blue.png";
	int graphicID;

	// ENEMY STATISTICS
	int speed = 4;
	bool death = false;

	// ANIMATION VARIABLES
	int frame = 0;
	float frameTime = 0;
	float eachTime = 250;

	// MOVIMENT
	int actualDirection;
	float moveTime = 0;
	float changeDirIn = 1000;

	rect Camera;

	// LEVEL REFERENCES
	mapLevel* map;
	int stageToCheck = -1;

	// COLLISION POINTS
	vector<point> CollisionPoints;

	// ALL TILE BLOCK ID'S COLLISIONS
	vector<vector<int>> availableCollisions =
	{
		// STAGE 1
		vector<int> {0},

		// STAGE 2
		vector<int> {1, 2, 5, 10, 11, 12, 13, 18, 21, 26, 29, 34, 37, 42, 43, 44, 45}
	};

	// CELL POSITION
	int cellX = -1;
	int cellY = -1;

	// LAST POSITION BEFORE COLLISION
	int lastX = -1;
	int lastY = -1;

public:
	eBlue();
	~eBlue();

	void update();
	void render();

	void setLevelRefrence(int stage, mapLevel* _map)
	{
		stageToCheck = stage;
		map = _map;
	}

	void setCamera(int X = 0, int Y = 0)
	{
		Camera.x = X;
		Camera.y = Y;
	}

	void setCollisionPoints();

	void checkTileCollision();

	void limitToScreen();
};

