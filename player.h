#pragma once
#include "gameObject.h"
#include "bomb.h"
#include "mapLevel.h"

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
	AudioManager* am;

	// GRAPHICS
	const char* graphicPath = "assets/player.png";
	int graphicID;

	int deadSound;

	// PLAYER STATISTICS
	float speed = 3;

	int maxBombs = 1;
	float bombTime = 0;
	float cooldownBomb = 250;
	int bombRange = 1;
	int defInmunityTime = 900;
	int inmunityTime = defInmunityTime;

	int lives = DEFAULT_LIVES;

	bool _isDead = false;

	bool inmortal = false;
	int inmortalTime = 2;
	int respawnTime;

	rect respawnPos, Camera;

	vector<bomb*>* generatedBombs;

	// ANIMATION VARIABLES
	int frame = 0;
	float frameTime = 0;
	float eachTime = 150;
	Animation  currentAnimation = WALKING_DOWN;
	bool idle = true;

	// LEVEL REFERENCES
	mapLevel* map;
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
		vector<int> {1, 2, 5, 10, 11, 12, 13, 18, 21, 26, 29, 34, 37, 42, 43, 44, 45}
	};

	void plantBomb();

public:
	player();
	~player();

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

	void limitPlayerToScreen();

	vector<bomb*>* getBombs()
	{
		return generatedBombs;
	}

	bool isDead()
	{
		return _isDead;
	}

	void respawn()
	{
		worldRect.x = respawnPos.x;
		worldRect.y = respawnPos.y;
	}

	int getLives()
	{
		return lives;
	}

	void addBombs()
	{
		maxBombs++;
	}

	void addSpeed()
	{
		if (speed < 6)
		{
			speed++;
		}
	}

	void addRadius()
	{
		bombRange++;
	}

	void addLives()
	{
		lives++;
	}

	void toggleInmortal(bool newInmortal, int time = 2)
	{
		inmortal = newInmortal;

		if (time <= 0)
		{
			inmortalTime = -1;
		}
		else
		{
			inmortalTime = time * 1000;
		}

		respawnTime = 0;
	}

	void setLives(int newLives)
	{
		lives = newLives;
	}

	void setAliveStatus(bool newStatus)
	{
		if (newStatus)
		{
			lives = DEFAULT_LIVES;
			_isDead = false;
		}
		else if(!inmortal && inmunityTime <= 0)
		{
			if (lives > 0)
			{
				lives--;
				am->playSound(-1, deadSound, 35, false);
				toggleInmortal(true);
				respawn();
			}
			else
			{
				_isDead = true;
			}
		}
	}
};

