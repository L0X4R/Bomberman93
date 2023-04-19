#include "player.h"

#define MARGIN_X 10

player::player()
{
	rm = nullptr;
	graphicID = -1;

	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	im = InputManager::getInstance();

	LOG("CREANDO AL JUGADOR...");

	graphicID = rm->loadAndGetGraphicID(graphicPath);
	generatedBombs = new vector<bomb*>;

	CollisionPoints.resize(CollisionPoint::ALL_POINTS);

	if (graphicID != -1 && generatedBombs != nullptr && rm != nullptr && vm != nullptr && im != nullptr)
	{
		thisRect.x = 0;
		thisRect.y = 0;
		thisRect.w = 60;
		thisRect.h = 92;

		worldRect.x = 68;
		worldRect.y = 10 + INTERFACE_MARGIN;
		worldRect.w = thisRect.w;
		worldRect.h = thisRect.h;

		setBotY(70);

		respawnPos.x = 68;
		respawnPos.y = 10 + INTERFACE_MARGIN;
		GOOD("EL JUGADOR SE HA CREADO CON EXITO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CREAR EL JUGADOR.");
		exit(1);
	}
}

player::~player()
{
}

void player::update()
{
	frameTime += vm->getDeltaTime();
	bombTime += vm->getDeltaTime();
	respawnTime += vm->getDeltaTime();
	inmunityTime -= vm->getDeltaTime();

	lastX = worldRect.x;
	lastY = worldRect.y;

	cellX = (worldRect.x + (worldRect.w / 2)) / TILE_SIZE;
	cellY = (worldRect.y + 70) / TILE_SIZE;


#pragma region STATE MACHINE
	if (!im->isKey_W() && !im->isKey_A() && !im->isKey_S() && !im->isKey_D())
	{
		idle = true;
	}

	if (im->isKey_W())
	{
		currentAnimation = WALKING_UP;
		worldRect.y -= speed;
		idle = false;
	}

	if (im->isKey_S())
	{
		currentAnimation = WALKING_DOWN;
		worldRect.y += speed;
		idle = false;
	}

	if (im->isKey_A())
	{
		currentAnimation = WALKING_LEFT;
		worldRect.x -= speed;
		idle = false;
	}

	if (im->isKey_D())
	{
		currentAnimation = WALKING_RIGHT;
		worldRect.x += speed;
		idle = false;
	}

	if (im->isKey_Space())
	{
		plantBomb();
	}
#pragma endregion

	limitPlayerToScreen();

	setCollisionPoints();

	checkTileCollision();

#pragma region CHECK EXPLODED BOMBS
	for (int bomb = 0; bomb < generatedBombs->size(); bomb++)
	{
		if (generatedBombs->at(bomb)->hasExploded())
		{
			generatedBombs->erase(generatedBombs->begin() + bomb);
			bomb--;
		}
	}
#pragma endregion

	if (inmortalTime > 0)
	{
		if (respawnTime >= inmortalTime)
		{
			respawnTime = 0;

			inmortal = false;
		}
	}

}

void player::plantBomb()
{
	if (maxBombs > generatedBombs->size())
	{
		if (bombTime >= cooldownBomb)
		{
			int cellX = (worldRect.x + worldRect.w / 2) / TILE_SIZE;
			int cellY = (worldRect.y + worldRect.h - 15) / TILE_SIZE;

			bool canGen = true;

			for (int bomb = 0; bomb < generatedBombs->size(); bomb++)
			{
				if (generatedBombs->at(bomb)->getPosition().x == cellX && generatedBombs->at(bomb)->getPosition().y == cellY)
				{
					canGen = false;
				}
			}

			if (canGen)
			{
				inmunityTime = defInmunityTime;
				bomb* newBomb = new bomb(cellX, cellY, bombRange, stageToCheck, map->getStaticMap(), map->getDynamicMap(), &availableCollisions);

				generatedBombs->push_back(newBomb);
			}

			bombTime = 0;
		}
	}
}

void player::render()
{
	rect worldCamPostion = worldRect;

	worldCamPostion.x -= Camera.x;

	if (frameTime >= eachTime)
	{
		frameTime = 0;
		frame++;
	}

	if (frame >= 3)
	{
		frame = 0;
	}

	if (inmortal)
	{
		vm->changeAlpha(graphicID, NULL, 120);
	}
	else
	{
		vm->changeAlpha(graphicID, NULL, 255);
	}

	if (idle)
	{
		thisRect.x = 0;
		thisRect.y = (currentAnimation * thisRect.h);
		vm->renderGraphic(graphicID, thisRect, worldCamPostion);
	}
	else
	{
		thisRect.x = (frame * thisRect.w);
		thisRect.y = (currentAnimation * thisRect.h);
		vm->renderGraphic(graphicID, thisRect, worldCamPostion);
	}

	//for (int i = 0; i < CollisionPoints.size(); i++)
	//{
	//	rect temp;

	//	temp.x = CollisionPoints[i].x;
	//	temp.y = CollisionPoints[i].y;

	//	temp.w = 2;
	//	temp.h = 2;

	//	vm->drawRect(temp);
	//}
}

void player::setCollisionPoints()
{
	CollisionPoints[TOP_LEFT].x = worldRect.x + MARGIN_X;
	CollisionPoints[TOP_LEFT].y = worldRect.y + bot_y;

	CollisionPoints[TOP_RIGHT].x = worldRect.x + worldRect.w - MARGIN_X;
	CollisionPoints[TOP_RIGHT].y = worldRect.y + bot_y;

	CollisionPoints[RIGHT_TOP].x = worldRect.x + worldRect.w - 5;
	CollisionPoints[RIGHT_TOP].y = worldRect.y + bot_y + 5;

	CollisionPoints[RIGHT_BOTTOM].x = worldRect.x + worldRect.w - 5;
	CollisionPoints[RIGHT_BOTTOM].y = worldRect.y + worldRect.h - 2;

	CollisionPoints[BOTTOM_LEFT].x = worldRect.x + MARGIN_X;
	CollisionPoints[BOTTOM_LEFT].y = worldRect.y + worldRect.h;

	CollisionPoints[BOTTOM_RIGHT].x = worldRect.x + worldRect.w - MARGIN_X;
	CollisionPoints[BOTTOM_RIGHT].y = worldRect.y + worldRect.h;

	CollisionPoints[LEFT_TOP].x = worldRect.x + 5;
	CollisionPoints[LEFT_TOP].y = worldRect.y + bot_y + 5;

	CollisionPoints[LEFT_BOTTOM].x = worldRect.x + 5;
	CollisionPoints[LEFT_BOTTOM].y = worldRect.y + worldRect.h - 2;
}

void player::checkTileCollision()
{
	if (map != nullptr)
	{
		rect tempTile;

		int xLimit;
		int yLimit;

		// LIMIT CELL TO CHECK [OPTIMIZATION] (300 loops => 25 loops)
		if (cellX < (map->getMapWidth() + 4))
		{
			xLimit = cellX + 4;
		}
		else
		{
			xLimit = cellX;
		}

		if (cellY < (map->getMapHeight() + 4))
		{
			yLimit = cellY + 4;
		}
		else
		{
			yLimit = cellY;
		}

		for (int y = cellY - 1; y < yLimit; y++)
		{
			for (int x = cellX - 1; x < xLimit; x++)
			{
				tempTile.x = x * 64;
				tempTile.y = y * 64 + INTERFACE_MARGIN;
				tempTile.w = 64;
				tempTile.h = 64;

				for (int cPoint = 0; cPoint < CollisionPoints.size(); cPoint++)
				{
					if (CheckCollision(tempTile, CollisionPoints[cPoint]) && (count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), map->getStaticMap()->at(y).at(x)) || count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), map->getDynamicMap()->at(y).at(x))))
					{

						if (cPoint == TOP_LEFT || cPoint == TOP_RIGHT || cPoint == BOTTOM_LEFT || cPoint == BOTTOM_RIGHT)
						{
							worldRect.y = lastY;
						}

						if (cPoint == RIGHT_TOP || cPoint == RIGHT_BOTTOM || cPoint == LEFT_TOP || cPoint == LEFT_BOTTOM)
						{
							worldRect.x = lastX;
						}
					}
				}
			}
		}
	}
}

void player::limitPlayerToScreen()
{
	if (worldRect.x < 0)
	{
		worldRect.x = 0;
	}

	if ((worldRect.x + worldRect.w) > map->getMapWidth() * map->getTileWidth())
	{
		worldRect.x = SCREEN_WIDTH - (map->getMapWidth() * map->getTileWidth());
	}

	if (worldRect.y < 0)
	{
		worldRect.y = 0;
	}

	if ((worldRect.y + worldRect.h) > map->getMapHeight() * map->getTileHeight())
	{
		worldRect.y = SCREEN_HEIGHT - (map->getMapHeight() * map->getTileHeight());
	}
}
