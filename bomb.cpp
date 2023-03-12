#include "bomb.h"

bomb::bomb(int cellX, int cellY)
{
	graphicID = -1;

	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	im = InputManager::getInstance();

	LOG("CREANDO BOMBA...");

	graphicID = rm->loadAndGetGraphicID(graphicPath);

	if (graphicID != -1 && rm != nullptr && vm != nullptr && im != nullptr)
	{
		int genPosX = (cellX * TILE_SIZE) + (TILE_SIZE / 2);
		int genPosY = (cellY * TILE_SIZE) + (TILE_SIZE / 2);

		position.x = cellX;
		position.y = cellY;

		objectRect.x = genPosX - (TILE_SIZE / 2);
		objectRect.y = genPosY - (TILE_SIZE / 2);

		objectRect.w = TILE_SIZE;
		objectRect.h = TILE_SIZE;
		GOOD("LA BOMBA SE HA CREADO CON EXITO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CREAR LA BOMBA.");
		exit(1);
	}
}

bomb::~bomb()
{
}

void bomb::update()
{
	bombTime += vm->getDeltaTime();

	if (bombTime >= explodeTime)
	{
		exploded = true;
	}

	if (exploded)
	{
		LOG("LA BOMBA HA EXPLOTADO!");
	}
}

void bomb::render()
{
	vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, 0);
}
