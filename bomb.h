#pragma once
#include "gameObject.h"
#include "hud.h"

enum explosionDir
{
	UP, DOWN, LEFT, RIGHT, ALL
};

struct explosionTile
{
	rect tile;
	point offset;
};

class bomb : public gameObject
{
private:
	ResourceManager* rm;
	AudioManager* am;
	VideoManager* vm;
	InputManager* im;

	const char* graphicPath = "assets/bombs.png";
	int graphicID;

	int explosionSound;

	int stage;
	vector<vector<int>>* levelReference;
	vector<vector<int>>* dynamicLevelReference;
	vector<vector<int>>* availableCollisions;

	bool exploding = false;
	bool exploded = false;
	bool breakedBlocks = false;

	vector<vector<explosionTile>> explotionGraph;

	hud* HUD;

	point position;

	rect Camera;

	float bombTime;
	float explodeTime = 900;
	int range = 1;

public:
	bomb(int cellX, int cellY, int bombRange, int _stage, vector<vector<int>>* level, vector<vector<int>>* dyLevel, vector<vector<int>>* collisions);
	~bomb();

	bool generateExplosion();

	void update();
	void render();

	bool isExploding()
	{
		return exploding;
	}

	bool hasExploded()
	{
		return exploded;
	}

	point getPosition()
	{
		return position;
	}

	void setCamera(int X = 0, int Y = 0)
	{
		Camera.x = X;
		Camera.y = Y;
	}

	bool breakedSomething()
	{
		return breakedBlocks;
	}

	void breakChecked()
	{
		breakedBlocks = false;
	}

	vector<vector<explosionTile>> getExplotion()
	{
		return explotionGraph;
	}
};

