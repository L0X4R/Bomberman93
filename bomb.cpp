#include "bomb.h"

bomb::bomb(int cellX, int cellY, int bombRange)
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

		range = bombRange;
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

void bomb::generateExplosion()
{
	int startX = objectRect.x + (TILE_SIZE / 2);
	int startY = objectRect.y;

	leftBoom.x = objectRect.x - (TILE_SIZE * range);
	leftBoom.y = objectRect.y;
	leftBoom.w = TILE_SIZE * range;
	leftBoom.h = TILE_SIZE;

	rightBoom.x = objectRect.x + TILE_SIZE;
	rightBoom.y = objectRect.y;
	rightBoom.w = TILE_SIZE * range;
	rightBoom.h = TILE_SIZE;

	topBoom.x = objectRect.x;
	topBoom.y = objectRect.y - (TILE_SIZE * range);
	topBoom.w = TILE_SIZE;
	topBoom.h = TILE_SIZE * range;

	bottomBoom.x = objectRect.x;
	bottomBoom.y = objectRect.y + TILE_SIZE;
	bottomBoom.w = TILE_SIZE;
	bottomBoom.h = TILE_SIZE * range;

	exploding = true;
}

void bomb::update()
{
	bombTime += vm->getDeltaTime();

	if (bombTime >= explodeTime && exploding == false)
	{
		generateExplosion();
		bombTime = 0;
	}

	if (exploding == true && bombTime >= explodeTime)
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

	if (exploding)
	{
		vm->drawRect(leftBoom);
		vm->drawRect(rightBoom);
		vm->drawRect(topBoom);
		vm->drawRect(bottomBoom);
	}
}
