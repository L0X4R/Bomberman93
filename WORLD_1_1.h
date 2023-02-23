#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "player.h"
#include "ResourceManager.h"
#include "VideoManager.h"
#include "tinyxml2.h"
#include "config.h"

class WORLD_1_1 : public Scene
{
private:
	ResourceManager* rm;
	VideoManager* vm;

	bool isMenuScene = false;

	player Jugador;

	const char* levelName = "LEVEL 1-1";
	const char* levelPath = "assets/maps/level.tmx";

	vector<vector<int>> levelData;

	const char* tilesetPath = "assets/maps/tileset.png";
	int tilesetID;

	quadTile rectS, rectT;

	int tileID;
	int cellX, cellY;

	int mapWidth = 32;
	int mapHeight = 24;

	int tileMargin = 1;
	int tileWidth = 32;
	int tileHeight = 32;


public:
	void render();

	void update();

	void loadXMLevel();
};

