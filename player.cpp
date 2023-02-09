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

	// LIMIT PLAYER POSITION TO SCREEN
	if (pos.x < 0)
	{
		pos.x = 0;
	}

	if ((pos.x + 60) > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - 60;
	}

	if (pos.y < 0)
	{
		pos.y = 0;
	}

	if ((pos.y + 92) > SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - 92;
	}
}

void player::renderAnimation(int frame)
{
	switch (currentAnimation)
	{
	case WALKING_DOWN:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 0, 0);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 60 * frame, 92 * currentAnimation);
		}
		break;
	case WALKING_UP:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 0, 92 * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 60 * frame, 92 * currentAnimation);
		}
		break;
	case WALKING_LEFT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 0, 92 * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 60 * frame, 92 * currentAnimation);
		}
		break;
	case WALKING_RIGHT:
		if (idle)
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 0, 92 * currentAnimation);
		}
		else
		{
			vm->renderGraphic(playerGraphicID, pos.x, pos.y, 60, 92, 60 * frame, 92 * currentAnimation);
		}
		break;
	default:
		break;
	}
}

void player::render()
{


	if (vm->getProcessTime() >= time)
	{
		time += 130;
		frame++;
	}

	if (frame >= 3)
	{
		frame = 0;
	}

	renderAnimation(frame);
}
