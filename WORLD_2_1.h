#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "player.h"
#include "ResourceManager.h"
#include "VideoManager.h"
#include "tinyxml2.h"
#include "mapLevel.h"
#include "hud.h"
#include "eBlue.h"
#include "config.h"

class WORLD_2_1 : public Scene
{
private:
	player Jugador;
	mapLevel _map;
	hud* HUD;

	vector<eBlue> blueEnemies;

	int CameraX;

	void spawnEnemies(int quantity);

	bool checkBombCollision(rect victim, int botY);

public:
	void initLevel();

	void update();

	void render();
};

