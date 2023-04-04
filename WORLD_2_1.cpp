#include "WORLD_2_1.h"

void WORLD_2_1::initLevel()
{
	_map.loadMap("LEVEL 2-1", "assets/maps/stage1.tmx", "assets/maps/stage2.png");

	Jugador.setLevelRefrence(2, &_map);

	CameraX = 0;
}

void WORLD_2_1::update()
{
	Jugador.update();

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
	
	// UPDATE ALL BOMBS OF PLAYER.
	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
		Jugador.getBombs()->at(bomb)->update();
	}

	// CHECK IF PLAYER COLLISION WITH BOMB FIRE IN 4 DIRECTIONS FOR EVERY RANGE.
	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
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

				if (Jugador.getRect().x + Jugador.getRect().w > tileX && tileX + tileW > Jugador.getRect().x) {
					OverlapsX = true;
				}
				if (Jugador.getRect().y + Jugador.getRect().h > tileY && tileY + tileH > (Jugador.getRect().y + 70)) {
					OverlapsY = true;
				}

				if (OverlapsX && OverlapsY)
				{
					Jugador.setLiveStatus(false);
					break;
				}
			}
		}
	}
}

void WORLD_2_1::render()
{
	_map.render();

	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
		Jugador.getBombs()->at(bomb)->render();
	}

	Jugador.render();
}
