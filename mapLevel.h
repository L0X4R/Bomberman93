#pragma once
#include "ResourceManager.h"
#include "VideoManager.h"
#include "tinyxml2.h"

#include <vector>
#include <sstream>

#define INTERFACE_MARGIN 64

using namespace std;

class mapLevel
{
private:
	ResourceManager* rm;
	VideoManager* vm;

	const char* levelName;
	const char* levelPath;
	const char* tilesetPath;

	vector<vector<int>> staticMap;
	vector<vector<int>> dynamicMap;

	rect rectS, rectT, Camera;

	int tilesetID;

	int mapWidth;
	int mapHeight;

	int tileMargin;
	int tileWidth;
	int tileHeight;

public:
	mapLevel();
	~mapLevel();

	void loadMap(const char* _levelName, const char* mapPath, const char* tilePath);

	void render();

	vector<vector<int>>* getStaticMap()
	{
		return &staticMap;
	}

	vector<vector<int>>* getDynamicMap()
	{
		return &dynamicMap;
	}

	void getCamera(int X = 0, int Y = 0)
	{
		Camera.x = X;
		Camera.y = Y;
	}

	int getMapWidth()
	{
		return mapWidth;
	}

	int getMapHeight()
	{
		return mapHeight;
	}

	int getTileMargin()
	{
		return tileMargin;
	}

	int getTileWidth()
	{
		return tileWidth;
	}

	int getTileHeight()
	{
		return tileWidth;
	}
};

