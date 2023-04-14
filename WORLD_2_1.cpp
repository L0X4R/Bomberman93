#include "WORLD_2_1.h"

void WORLD_2_1::initLevel()
{
	_map.loadMap("LEVEL 2-1", "assets/maps/s2m1.tmx", "assets/maps/ice.png");

	Jugador.setLevelRefrence(2, &_map);

	spawnEnemies(8);
	
	for (int enemy = 0; enemy < blueEnemies.size(); enemy++)
	{
		blueEnemies[enemy].setLevelRefrence(2, &_map);
	}

	CameraX = 0;

	HUD = hud::getInstance();
}

void WORLD_2_1::update()
{
	Jugador.update();

	for (int enemy = 0; enemy < blueEnemies.size(); enemy++)
	{
		blueEnemies[enemy].update();
	}

	CameraX = (Jugador.getRect().x - SCREEN_WIDTH / 2);

	if (CameraX > _map.getMapWidth() * _map.getTileWidth() - SCREEN_WIDTH)
	{
		CameraX = _map.getMapWidth() * _map.getTileWidth() - SCREEN_WIDTH;
	}

	if (CameraX < 0)
	{
		CameraX = 0;
	}

	_map.getCamera(CameraX);
	Jugador.setCamera(CameraX);

	for (int enemy = 0; enemy < blueEnemies.size(); enemy++)
	{
		blueEnemies[enemy].setCamera(CameraX);
	}
	
	// UPDATE ALL BOMBS OF PLAYER.
	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
		Jugador.getBombs()->at(bomb)->update();
		Jugador.getBombs()->at(bomb)->setCamera(CameraX);
	}

	if (checkBombCollision(Jugador.getRect(), Jugador.getBotY()))
	{
		Jugador.setAliveStatus(false);
	}

	for (int enemy = 0; enemy < blueEnemies.size(); enemy++)
	{
		if (checkBombCollision(blueEnemies[enemy].getRect(), blueEnemies[enemy].getBotY()))
		{
			HUD->addScore(200);
			blueEnemies.erase(blueEnemies.begin() + enemy);
			enemy--;
		}
	}

	HUD->setLives(Jugador.getLives());
	HUD->update();
}

void WORLD_2_1::render()
{
	_map.render();

	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
		Jugador.getBombs()->at(bomb)->render();
	}

	HUD->render();

	for (int enemy = 0; enemy < blueEnemies.size(); enemy++)
	{
		blueEnemies[enemy].render();
	}

	Jugador.render();
}

void WORLD_2_1::spawnEnemies(int quantity = 2)
{
	blueEnemies.resize(quantity);

	for (int enemy = 0; enemy < blueEnemies.size(); enemy++)
	{
		bool spawned = false;

		while (!spawned)
		{
			int randX = rand() % _map.getMapWidth();
			int randY = rand() % _map.getMapHeight();

			int dyTile = _map.getDynamicMap()->at(randY).at(randX);
			int stTile = _map.getStaticMap()->at(randY).at(randX);

			if ((dyTile == 0 && stTile == 3) && randX > 2 && randY > 2)
			{
				int positionX = ((randX * TILE_SIZE) + (TILE_SIZE / 2) - (blueEnemies[enemy].getRect().w / 2));
				int positionY = ((randY * TILE_SIZE) + (TILE_SIZE / 2) - (blueEnemies[enemy].getRect().h / 2)) + INTERFACE_MARGIN;

				blueEnemies[enemy].setPosition(positionX, positionY);
				spawned = true;
			}
		}
	}
}

bool WORLD_2_1::checkBombCollision(rect victim, int botY)
{
	// CHECK IF VICTIM COLLISION WITH BOMB FIRE IN 4 DIRECTIONS FOR EVERY RANGE.
	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
		bool OverlapsX = false;
		bool OverlapsY = false;

		rect bombRect = Jugador.getBombs()->at(bomb)->getRect();

		if (victim.x + victim.w > bombRect.x && bombRect.x + bombRect.w > victim.x) {
			OverlapsX = true;
		}
		if (victim.y + victim.h > bombRect.y && bombRect.y + bombRect.h > (victim.y + botY)) {
			OverlapsY = true;
		}

		if (OverlapsX && OverlapsY)
		{
			return true;
		}

		for (int dir = 0; dir < Jugador.getBombs()->at(bomb)->getExplotion().size(); dir++)
		{
			for (int rng = 0; rng < Jugador.getBombs()->at(bomb)->getExplotion().at(dir).size(); rng++)
			{
				int tileX = Jugador.getBombs()->at(bomb)->getExplotion().at(dir).at(rng).tile.x;
				int tileY = Jugador.getBombs()->at(bomb)->getExplotion().at(dir).at(rng).tile.y;
				int tileW = Jugador.getBombs()->at(bomb)->getExplotion().at(dir).at(rng).tile.w;
				int tileH = Jugador.getBombs()->at(bomb)->getExplotion().at(dir).at(rng).tile.h;

				bool OverlapsX = false;
				bool OverlapsY = false;

				if (victim.x + victim.w > tileX && tileX + tileW > victim.x) {
					OverlapsX = true;
				}
				if (victim.y + victim.h > tileY && tileY + tileH > (victim.y + botY)) {
					OverlapsY = true;
				}

				if (OverlapsX && OverlapsY)
				{
					return true;
				}
			}
		}
	}

	return false;
}
