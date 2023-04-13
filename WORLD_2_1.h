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
#include "config.h"

class WORLD_2_1 : public Scene
{
private:
	player Jugador;
	mapLevel _map;
	hud HUD;

	int CameraX;

public:
	void initLevel();

	void update();

	void render();
};

