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
		objectRect.x = 68;
		objectRect.y = 10;
		objectRect.w = 60;
		objectRect.h = 92;
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

	lastX = objectRect.x;
	lastY = objectRect.y;

#pragma region STATE MACHINE
	if (!im->isKey_W() && !im->isKey_A() && !im->isKey_S() && !im->isKey_D())
	{
		idle = true;
	}

	if (im->isKey_W())
	{
		currentAnimation = WALKING_UP;
		objectRect.y -= speed;
		idle = false;
	}

	if (im->isKey_A())
	{
		currentAnimation = WALKING_LEFT;
		objectRect.x -= speed;
		idle = false;
	}

	if (im->isKey_S())
	{
		currentAnimation = WALKING_DOWN;
		objectRect.y += speed;
		idle = false;
	}

	if (im->isKey_D())
	{
		currentAnimation = WALKING_RIGHT;
		objectRect.x += speed;
		idle = false;
	}

	if (im->isKey_Space())
	{
		plantBomb();
	}
#pragma endregion

#pragma region LIMIT SCREEN
	// LIMIT PLAYER POSITION TO SCREEN
	if (objectRect.x < 0)
	{
		objectRect.x = 0;
	}

	if ((objectRect.x + objectRect.w) > SCREEN_WIDTH)
	{
		objectRect.x = SCREEN_WIDTH - objectRect.w;
	}

	if (objectRect.y < 0)
	{
		objectRect.y = 0;
	}

	if ((objectRect.y + objectRect.h) > SCREEN_HEIGHT)
	{
		objectRect.y = SCREEN_HEIGHT - objectRect.h;
	}
#pragma endregion

#pragma region CHECK COLLISION
	CollisionPoints[TOP_LEFT].x = objectRect.x + H_MARGIN;
	CollisionPoints[TOP_LEFT].y = objectRect.y + 70;

	CollisionPoints[TOP_RIGHT].x = objectRect.x + objectRect.w - H_MARGIN;
	CollisionPoints[TOP_RIGHT].y = objectRect.y + 70;

	CollisionPoints[RIGHT_TOP].x = objectRect.x + objectRect.w - X_MARGIN;
	CollisionPoints[RIGHT_TOP].y = objectRect.y + 70 + V_MARGIN;

	CollisionPoints[RIGHT_BOTTOM].x = objectRect.x + objectRect.w - X_MARGIN;
	CollisionPoints[RIGHT_BOTTOM].y = objectRect.y + objectRect.h - V_MARGIN;

	CollisionPoints[BOTTOM_LEFT].x = objectRect.x + H_MARGIN;
	CollisionPoints[BOTTOM_LEFT].y = objectRect.y + objectRect.h;

	CollisionPoints[BOTTOM_RIGHT].x = objectRect.x + objectRect.w - H_MARGIN;
	CollisionPoints[BOTTOM_RIGHT].y = objectRect.y + objectRect.h;

	CollisionPoints[LEFT_TOP].x = objectRect.x + X_MARGIN;
	CollisionPoints[LEFT_TOP].y = objectRect.y + 70 + V_MARGIN;

	CollisionPoints[LEFT_BOTTOM].x = objectRect.x + X_MARGIN;
	CollisionPoints[LEFT_BOTTOM].y = objectRect.y + objectRect.h - V_MARGIN;

	if (levelReference != nullptr)
	{
		objRect tempTile;

		for (int y = 0; y < levelReference->size(); y++)
		{
			for (int x = 0; x < levelReference->at(y).size(); x++)
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
							objectRect.y = lastY;
						}

						if (cPoint == RIGHT_TOP || cPoint == RIGHT_BOTTOM || cPoint == LEFT_TOP || cPoint == LEFT_BOTTOM)
						{
							objectRect.x = lastX;
						}
					}
				}
			}
		}
	}
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
			int cellX = (objectRect.x + objectRect.w / 2) / TILE_SIZE;
			int cellY = (objectRect.y + objectRect.h - 15) / TILE_SIZE;

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
				bomb* newBomb = new bomb(cellX, cellY);

				generatedBombs->push_back(newBomb);
			}

			bombTime = 0;
		}
	}
}

void player::renderAnimation(int frame)
{
	switch (currentAnimation)
	{
	case WALKING_DOWN:
		if (idle)
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, 0);
		}
		else
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	case WALKING_UP:
		if (idle)
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, objectRect.h * currentAnimation);
		}
		else
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	case WALKING_LEFT:
		if (idle)
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, objectRect.h * currentAnimation);
		}
		else
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	case WALKING_RIGHT:
		if (idle)
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, objectRect.h * currentAnimation);
		}
		else
		{
			vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	default:
		break;
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

	renderAnimation(frame);

	//for (int i = 0; i < CollisionPoints.size(); i++)
	//{
	//	vm->drawPoint(CollisionPoints[i].x, CollisionPoints[i].y);
	//}
}
