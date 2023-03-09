#include "player.h"

player::player()
{
	rm = nullptr;
	playerGraphicID = -1;

	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	im = InputManager::getInstance();

	LOG("CREANDO AL JUGADOR...");

	playerGraphicID = rm->loadAndGetGraphicID(graphicPath);

	CollisionPoints.resize(CollisionPoint::ALL_POINTS);

	if (playerGraphicID != -1 && rm != nullptr && vm != nullptr && im != nullptr)
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
	rm->removeGraphic(graphicPath);
}

void player::update()
{
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
	CollisionPoints[TOP_LEFT].x = objectRect.x + COL_MARGIN;
	CollisionPoints[TOP_LEFT].y = objectRect.y + 82 - COL_MARGIN;

	CollisionPoints[TOP_RIGHT].x = objectRect.x + objectRect.w - COL_MARGIN;
	CollisionPoints[TOP_RIGHT].y = objectRect.y + 82 - COL_MARGIN;

	CollisionPoints[RIGHT_TOP].x = (objectRect.x + objectRect.w) + COL_MARGIN;
	CollisionPoints[RIGHT_TOP].y = objectRect.y + 82;

	CollisionPoints[RIGHT_BOTTOM].x = (objectRect.x + objectRect.w) + COL_MARGIN;
	CollisionPoints[RIGHT_BOTTOM].y = objectRect.y + objectRect.h;

	CollisionPoints[BOTTOM_LEFT].x = objectRect.x;
	CollisionPoints[BOTTOM_LEFT].y = (objectRect.y + objectRect.h) + COL_MARGIN;

	CollisionPoints[BOTTOM_RIGHT].x = objectRect.x + objectRect.w;
	CollisionPoints[BOTTOM_RIGHT].y = (objectRect.y + objectRect.h) + COL_MARGIN;

	CollisionPoints[LEFT_TOP].x = objectRect.x - COL_MARGIN;
	CollisionPoints[LEFT_TOP].y = objectRect.y + 82;

	CollisionPoints[LEFT_BOTTOM].x = objectRect.x - COL_MARGIN;
	CollisionPoints[LEFT_BOTTOM].y = objectRect.y + objectRect.h;

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
						switch (cPoint)
						{
						case TOP_LEFT:
							objectRect.y = lastY;
							break;
						case TOP_RIGHT:
							objectRect.y = lastY;
							break;
						case RIGHT_TOP:
							objectRect.x = lastX;
							break;
						case RIGHT_BOTTOM:
							objectRect.x = lastX;
							break;
						case BOTTOM_LEFT:
							objectRect.y = lastY;
							break;
						case BOTTOM_RIGHT:
							objectRect.y = lastY;
							break;
						case LEFT_TOP:
							objectRect.x = lastX;
							break;
						case LEFT_BOTTOM:
							objectRect.x = lastX;
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}
#pragma endregion
}

void player::renderAnimation(int frame)
{
	switch (currentAnimation)
	{
	case WALKING_DOWN:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, 0);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	case WALKING_UP:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, objectRect.h * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	case WALKING_LEFT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, objectRect.h * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	case WALKING_RIGHT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, objectRect.h * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, objectRect.w * frame, objectRect.h * currentAnimation);
		}
		break;
	default:
		break;
	}
}

void player::render()
{
	frameTime += vm->getDeltaTime();

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

	for (int i = 0; i < CollisionPoints.size(); i++)
	{
		vm->drawPoint(CollisionPoints[i].x, CollisionPoints[i].y);
	}
}
