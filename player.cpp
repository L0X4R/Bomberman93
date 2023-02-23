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
	if (!im->isKey_W() && !im->isKey_A() && !im->isKey_S() && !im->isKey_D())
	{
		idle = true;
	}

	if (im->isKey_W())
	{
		pos.y -= speed;
		currentAnimation = WALKING_UP;
		idle = false;
	}

	if (im->isKey_A())
	{
		pos.x -= speed;
		currentAnimation = WALKING_LEFT;
		idle = false;
	}

	if (im->isKey_S())
	{
		pos.y += speed;
		currentAnimation = WALKING_DOWN;
		idle = false;
	}

	if (im->isKey_D())
	{
		pos.x += speed;
		currentAnimation = WALKING_RIGHT;
		idle = false;
	}
#pragma endregion

#pragma region LIMIT SCREEN
	// LIMIT PLAYER POSITION TO SCREEN
	if (pos.x < 0)
	{
		pos.x = 0;
	}

	if ((pos.x + 64) > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - 64;
	}

	if (pos.y < 0)
	{
		pos.y = 0;
	}

	if ((pos.y + 95) > SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - 95;
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
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 0, 0);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 64 * frame, 95 * currentAnimation);
		}
		break;
	case WALKING_UP:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 0, 95 * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 64 * frame, 95 * currentAnimation);
		}
		break;
	case WALKING_LEFT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 0, 95 * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 64 * frame, 95 * currentAnimation);
		}
		break;
	case WALKING_RIGHT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 0, 95 * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 64, 95, 64 * frame, 95 * currentAnimation);
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
