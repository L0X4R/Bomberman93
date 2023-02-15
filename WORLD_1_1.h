#pragma once
#include "Scene.h"
#include <iostream>
#include "player.h"
#include "VideoManager.h"
#include "tinyxml2.h"
#include "config.h"

class WORLD_1_1 : public Scene
{
private:
	player Jugador;
	string dataLevel = "";

public:
	void render();

	void update();

	void loadXMLevel();
};

