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
#pragma region STATE MACHINE
	lastPosX = objectRect.x;
	lastPosY = objectRect.y;

	collision.x = objectRect.x;
	collision.y = objectRect.y + 82;
	collision.w = objectRect.w;
	collision.h = 10;

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
	if (levelReference !=nullptr)
	{
		objRect tempTile;
		bool Overlaps = false;

		for (int y = 0; y < levelReference->size(); y++)
		{
			for (int x = 0; x < levelReference->at(y).size(); x++)
			{
				tempTile.x = x * 64;
				tempTile.y = y * 64;
				tempTile.w = 64;
				tempTile.h = 64;

				Overlaps = (CheckCollision(collision, tempTile));

				if (Overlaps && count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), levelReference->at(y).at(x)))
				{
					objectRect.x = lastPosX;
					objectRect.y = lastPosY;
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
}
