#include "player.h"

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
		worldRect.y = 10;
		worldRect.w = thisRect.w;
		worldRect.h = thisRect.h;

		respawnPos.x = 68;
		respawnPos.y = 10;
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

	lastX = worldRect.x;
	lastY = worldRect.y;

	cellX = (worldRect.x + (worldRect.w / 2)) / TILE_SIZE;
	cellY = (worldRect.y + 70) / TILE_SIZE;

	//printf("CELL X: %d CELL Y: %d      \r", cellX, cellY);

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

#pragma region LIMIT SCREEN
	// LIMIT PLAYER POSITION TO SCREEN
	if (worldRect.x < 0)
	{
		worldRect.x = 0;
	}

	if ((worldRect.x + worldRect.w) > SCREEN_WIDTH)
	{
		worldRect.x = SCREEN_WIDTH - worldRect.w;
	}

	if (worldRect.y < 0)
	{
		worldRect.y = 0;
	}

	if ((worldRect.y + worldRect.h) > SCREEN_HEIGHT)
	{
		worldRect.y = SCREEN_HEIGHT - worldRect.h;
	}
#pragma endregion

#pragma region CHECK COLLISION
	setCollisionPoints();

	updateCollision();
#pragma endregion

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
				bomb* newBomb = new bomb(cellX, cellY, bombRange, stageToCheck, levelReference, &availableCollisions);

				generatedBombs->push_back(newBomb);
			}

			bombTime = 0;
		}
	}
}

void player::render()
{
	if (frameTime >= eachTime)
	{
		frameTime = 0;
		frame++;
	}

	if (frame >= 3)
	{
		frame = 0;
	}

	if (idle)
	{
		thisRect.x = 0;
		thisRect.y = (currentAnimation * thisRect.h);
		vm->renderGraphic(graphicID, thisRect, worldRect);
	}
	else
	{
		thisRect.x = (frame * thisRect.w);
		thisRect.y = (currentAnimation * thisRect.h);
		vm->renderGraphic(graphicID, thisRect, worldRect);
	}

	//for (int i = 0; i < CollisionPoints.size(); i++)
	//{
	//	vm->drawPoint(CollisionPoints[i].x, CollisionPoints[i].y);
	//}
}

void player::setCollisionPoints()
{
	CollisionPoints[TOP_LEFT].x = worldRect.x + H_MARGIN;
	CollisionPoints[TOP_LEFT].y = worldRect.y + 70;

	CollisionPoints[TOP_RIGHT].x = worldRect.x + worldRect.w - H_MARGIN;
	CollisionPoints[TOP_RIGHT].y = worldRect.y + 70;

	CollisionPoints[RIGHT_TOP].x = worldRect.x + worldRect.w - X_MARGIN;
	CollisionPoints[RIGHT_TOP].y = worldRect.y + 70 + V_MARGIN;

	CollisionPoints[RIGHT_BOTTOM].x = worldRect.x + worldRect.w - X_MARGIN;
	CollisionPoints[RIGHT_BOTTOM].y = worldRect.y + worldRect.h - V_MARGIN;

	CollisionPoints[BOTTOM_LEFT].x = worldRect.x + H_MARGIN;
	CollisionPoints[BOTTOM_LEFT].y = worldRect.y + worldRect.h;

	CollisionPoints[BOTTOM_RIGHT].x = worldRect.x + worldRect.w - H_MARGIN;
	CollisionPoints[BOTTOM_RIGHT].y = worldRect.y + worldRect.h;

	CollisionPoints[LEFT_TOP].x = worldRect.x + X_MARGIN;
	CollisionPoints[LEFT_TOP].y = worldRect.y + 70 + V_MARGIN;

	CollisionPoints[LEFT_BOTTOM].x = worldRect.x + X_MARGIN;
	CollisionPoints[LEFT_BOTTOM].y = worldRect.y + worldRect.h - V_MARGIN;
}

void player::updateCollision()
{
	if (levelReference != nullptr)
	{
		rect tempTile;

		int xLimit;
		int yLimit;

		// LIMIT CELL TO CHECK [OPTIMIZATION] (300 loops => 25 loops)
		if (cellX < (MAP_WIDTH + 4))
		{
			xLimit = cellX + 4;
		}
		else
		{
			xLimit = cellX;
		}

		if (cellY < (MAP_HEIGHT + 4))
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
				tempTile.y = y * 64;
				tempTile.w = 64;
				tempTile.h = 64;

				for (int cPoint = 0; cPoint < CollisionPoints.size(); cPoint++)
				{
					if (CheckCollision(tempTile, CollisionPoints[cPoint]) && count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), levelReference->at(y).at(x)))
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
