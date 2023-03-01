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

	player Jugador;

	const char* levelName = "LEVEL 1-1";
	const char* levelPath = "assets/maps/stage2.tmx";

	vector<vector<int>> levelData;

	const char* tilesetPath = "assets/maps/stage2.png";
	int tilesetID;

	quadTile rectS, rectT;

	int tileID;
	int cellX, cellY;

	int mapWidth = 20;
	int mapHeight = 15;

	int tileMargin = 4;
	int tileWidth = 64;
	int tileHeight = 64;


public:
	void render();

	void update();

	void loadXMLevel();
};

