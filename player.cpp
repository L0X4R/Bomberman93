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
}

void player::render()
{
	vm->renderGraphic(playerGraphicID, pos.x, pos.y, size.w, size.h);
}
