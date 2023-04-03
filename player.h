#pragma once
#include "gameObject.h"
#include "bomb.h"

#define V_MARGIN 5
#define H_MARGIN 15
#define X_MARGIN 8

#define DEFAULT_LIVES 3

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
	// MANAGERS
	ResourceManager* rm;
	VideoManager* vm;
	InputManager * im;

	// GRAPHICS
	const char* graphicPath = "assets/player.png";
	int graphicID;

	// PLAYER STATISTICS
	int speed = 4;

	int maxBombs = 3;
	float bombTime = 0;
	float cooldownBomb = 250;
	int bombRange = 2;

	int lives = DEFAULT_LIVES;

	bool isDead = false;

	rect respawnPos;

	vector<bomb*>* generatedBombs;

	// ANIMATION VARIABLES
	int frame = 0;
	float frameTime = 0;
	float eachTime = 150;
	Animation  currentAnimation = WALKING_DOWN;
	bool idle = true;

	// LEVEL REFERENCES
	vector<vector<int>>* levelReference;
	int stageToCheck = -1;

	// COLLISION POINTS
	vector<point> CollisionPoints;

	// CELL POSITION
	int cellX = -1;
	int cellY = -1;

	// LAST POSITION BEFORE COLLISION
	int lastX = -1;
	int lastY = -1;

	// ALL TILE BLOCK ID'S COLLISIONS
	vector<vector<int>> availableCollisions =
	{
		// STAGE 1
		vector<int> {0},

		// STAGE 2
		vector<int> {2, 5, 10, 11, 12, 13, 18, 21, 26, 29, 34, 37, 42, 43, 44, 45}
	};

	void plantBomb();

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

	void setCollisionPoints();

	void updateCollision();

	vector<bomb*>* getBombs()
	{
		return generatedBombs;
	}

	bool getLiveStatus()
	{
		return isDead;
	}

	void respawn()
	{
		worldRect.x = respawnPos.x;
		worldRect.y = respawnPos.y;
	}

	void setLiveStatus(bool newStatus)
	{
		if (newStatus)
		{
			lives = DEFAULT_LIVES;
			isDead = false;
		}
		else
		{
			if (lives > 0)
			{
				lives--;
				printf("LIVES: %d\n", lives);
				respawn();
			}
			else
			{
				isDead = true;
			}
		}
	}
};

