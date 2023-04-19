#include "powerUp.h"

powerUp::powerUp(int posX, int posY, int genPowerType)
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();

	type = genPowerType;

	thisRect.x = 0;
	thisRect.y = 0;
	thisRect.w = 32;
	thisRect.h = 32;

	worldRect.x = posX;
	worldRect.y = posY;
	worldRect.w = thisRect.w;
	worldRect.h = thisRect.h;

	graphicID = rm->loadAndGetGraphicID(graphicPath);

	if (rm != nullptr && vm != nullptr && graphicID != -1)
	{
		LOG("GENERATED POWER UP!");
	}
	else
	{
		ERROR("NO SE HA PODIDO GENERAR EL POWER UP.");
	}
}

powerUp::~powerUp()
{
}

void powerUp::update()
{
	liveTime -= vm->getDeltaTime();
}

void powerUp::render()
{
	rect worldCamPostion = worldRect;

	worldCamPostion.x -= Camera.x;

	thisRect.x = (type * thisRect.w);
	vm->renderGraphic(graphicID, thisRect, worldCamPostion);
}
