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

	rm->getGraphicSize(playerGraphicID, size.w, size.h);

	if (playerGraphicID != -1 && rm != nullptr && vm != nullptr && im != nullptr)
	{
		pos.x = 68;
		pos.y = 10;
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
	lastPosX = pos.x;
	lastPosY = pos.y;

	if (!im->isKey_W() && !im->isKey_A() && !im->isKey_S() && !im->isKey_D())
	{
		idle = true;
	}

	if (im->isKey_W())
	{
		currentAnimation = WALKING_UP;
		pos.y -= speed;
		idle = false;
	}

	if (im->isKey_A())
	{
		currentAnimation = WALKING_LEFT;
		pos.x -= speed;
		idle = false;
	}

	if (im->isKey_S())
	{
		currentAnimation = WALKING_DOWN;
		pos.y += speed;
		idle = false;
	}

	if (im->isKey_D())
	{
		currentAnimation = WALKING_RIGHT;
		pos.x += speed;
		idle = false;
	}
#pragma endregion

#pragma region LIMIT SCREEN
	// LIMIT PLAYER POSITION TO SCREEN
	if (pos.x < 0)
	{
		pos.x = 0;
	}

	if ((pos.x + pWidth) > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - pWidth;
	}

	if (pos.y < 0)
	{
		pos.y = 0;
	}

	if ((pos.y + pHeight) > SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - pHeight;
	}
#pragma endregion

#pragma region CHECK COLLISION
	if (levelReference !=nullptr)
	{
		cellPosX = ((pos.x + (pWidth / 2)) / 64);
		cellPosY = ((pos.y + pHeight) / 64);

		switch (stageToCheck)
		{
		case 1:
			break;
		case 2:
			for (int y = 0; y < levelReference->size(); y++)
			{
				for (int x = 0; x < levelReference->at(y).size(); x++)
				{
					int cellLeft = pos.x / 64;
					int cellRight = (pos.x + pWidth) / 64;
					int cellTop = (pos.y + 70) / 64;
					int cellBottom = (pos.y + pHeight) / 64;

					if (cellLeft == x && cellPosY == y)
					{
						if (count(availableCollisions[stageToCheck-1].begin(), availableCollisions[stageToCheck-1].end(), levelReference->at(y).at(x)))
						{
							if (im->isKey_A())
							{
								pos.x = lastPosX;
								pos.y = lastPosY;
							}
						}
					}

					if (cellRight == x && cellPosY == y)
					{
						if (count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), levelReference->at(y).at(x)))
						{
							if (im->isKey_D())
							{
								pos.x = lastPosX;
								pos.y = lastPosY;
							}
						}
					}

					if (cellTop == y && cellPosX == x)
					{
						if (count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), levelReference->at(y).at(x)))
						{
							if (im->isKey_W())
							{
								pos.x = lastPosX;
								pos.y = lastPosY;
							}
						}
					}

					if (cellBottom == y && cellPosX == x)
					{
						if (count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), levelReference->at(y).at(x)))
						{
							if (im->isKey_S())
							{
								pos.x = lastPosX;
								pos.y = lastPosY;
							}
						}
					}
				}
			}
			break;
		default:
			break;
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
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, 0, 0);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, pWidth * frame, pHeight * currentAnimation);
		}
		break;
	case WALKING_UP:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, 0, pHeight * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, pWidth * frame, pHeight * currentAnimation);
		}
		break;
	case WALKING_LEFT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, 0, pHeight * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, pWidth * frame, pHeight * currentAnimation);
		}
		break;
	case WALKING_RIGHT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, 0, pHeight * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, pWidth, pHeight, pWidth * frame, pHeight * currentAnimation);
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
