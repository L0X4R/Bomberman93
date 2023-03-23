#pragma once
#include "gameObject.h"

enum explosionDir
{
	UP, DOWN, LEFT, RIGHT, ALL
};

struct explosionTile
{
	objRect tile;
	point offset;
};

class bomb : public gameObject
{
private:
	ResourceManager* rm;
	VideoManager* vm;
	InputManager* im;

	const char* graphicPath = "assets/bombs.png";
	int graphicID;

	int stage;
	vector<vector<int>>* levelReference;
	vector<vector<int>>* availableCollisions;

	bool exploding = false;
	bool exploded = false;

	vector<vector<explosionTile>> explotionGraph;

	point position;

	float bombTime;
	float explodeTime = 2000;
	int range = 1;

public:
	bomb(int cellX, int cellY, int bombRange, int _stage, vector<vector<int>>* level, vector<vector<int>>* collisions);
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

	vector<vector<explosionTile>> getExplotion()
	{
		return explotionGraph;
	}
};

