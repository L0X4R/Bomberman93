#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "player.h"
#include "ResourceManager.h"
#include "VideoManager.h"
#include "TextManager.h"
#include "tinyxml2.h"
#include "mapLevel.h"
#include "hud.h"
#include "eBlue.h"
#include "eOrange.h"
#include "config.h"

class WORLD_2_1 : public Scene
{
	struct AllEnemies
	{
		vector<eBlue> blueEnemies;
		vector<eOrange> orangeEnemies;
	};

private:
	player Jugador;
	mapLevel _map;
	hud* HUD;
	TextManager* tm;

	AllEnemies mapEnemies;

	int CameraX;

	// --------------------------

	void refEnemies();

	void spawnEnemies(int blueQuantity, int orangeQuantity);

	void updateEnemies();

	void checkEnemies();

	void renderEnemies();

	// --------------------------

	void calculateCamera();

	bool checkBombCollision(rect victim, int botY);

	bool checkEntitiesCollision(rect victim, int victimBotY, rect enemy, int enemyBotY);

public:
	void initLevel();

	void update();

	void render();
};

