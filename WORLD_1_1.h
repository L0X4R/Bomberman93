#pragma once
#include "Scene.h"
#include "player.h"
#include "VideoManager.h"

class WORLD_1_1 : public Scene
{
private:
	player Jugador;

public:
	void render();

	void update();
};

