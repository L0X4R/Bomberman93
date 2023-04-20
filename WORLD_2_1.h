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
#include "powerUp.h"
#include "hud.h"
#include "enemy.h"
#include "config.h"

class WORLD_2_1 : public Scene
{
private:
	ResourceManager* rm;
	AudioManager* am;

	player Jugador;
	mapLevel _map;
	hud* HUD;
	TextManager* tm;

	vector<powerUp*> powerUps;
	vector<enemy*> enemies;

	int backgroundMusic;
	int impactSound;
	int levelCompleteSound;
	int pickUpSound;


	int CameraX;

	void spawnEnemies(int quantity);

	void calculateCamera();

	bool checkBombCollision(rect victim, int botY);

	bool checkEntitiesCollision(rect victim, int victimBotY, rect enemy, int enemyBotY);

	void generatePowerUp(int x, int y);

public:
	void initLevel();

	void update();

	void render();
};

