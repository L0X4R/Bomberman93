#include "WORLD_2_1.h"

void WORLD_2_1::initLevel()
{
	_map.loadMap("LEVEL 2-1", "assets/maps/s2m1.tmx", "assets/maps/ice.png");

	Jugador.setLevelRefrence(2, &_map);

	spawnEnemies(5, 8);

	refEnemies();

	CameraX = 0;

	HUD = hud::getInstance();
	tm = TextManager::getInstance();
}

void WORLD_2_1::update()
{
	// PLAYER UPDATE
	Jugador.update();

	// UPDATE ALL ENEMIES
	updateEnemies();

	// UPDATE AND SET CAMERAS
	calculateCamera();
	
	// UPDATE ALL BOMBS OF PLAYER.
	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
		Jugador.getBombs()->at(bomb)->update();
		Jugador.getBombs()->at(bomb)->setCamera(CameraX);

		if (Jugador.getBombs()->at(bomb)->breakedSomething())
		{
			int posX = Jugador.getBombs()->at(bomb)->getPosition().x;
			int posY = Jugador.getBombs()->at(bomb)->getPosition().y;
			generatePowerUp(posX, posY);
			Jugador.getBombs()->at(bomb)->breakChecked();
		}
	}

	// CHECK IF PLAYER COLLISIO WITH FIRE BOMB.
	if (checkBombCollision(Jugador.getRect(), Jugador.getBotY()))
	{
		Jugador.setAliveStatus(false);
	}

	// CHECK IF ENEMY COLLISIONS.
	checkEnemies();

	// UPDATE HUD LIVES
	HUD->setLives(Jugador.getLives());

	// UPDATE HUD
	HUD->update();

	for (int power = 0; power < powerUps.size(); power++)
	{
		powerUps.at(power)->setCamera(CameraX);

		powerUps.at(power)->update();

		if (powerUps.at(power)->remainingTime() <= 0)
		{
			powerUps.erase(powerUps.begin() + power);
			power--;
		}
	}

	for (int power = 0; power < powerUps.size(); power++)
	{
		powerUps.at(power)->setCamera(CameraX);

		if (checkEntitiesCollision(Jugador.getRect(), Jugador.getBotY(), powerUps.at(power)->getRect(), 0))
		{
			switch (powerUps.at(power)->getType())
			{
			case PlusBomb:
				Jugador.addBombs();
				break;
			case RemoteControl:
				break;
			case PlusRadius:
				Jugador.addRadius();
				break;
			case PlusSpeed:
				Jugador.addSpeed();
				break;
			case PlusLives:
				Jugador.addLives();
				break;
			case PlusScore:
				HUD->addScore(500);
				break;
			default:
				break;
			}

			powerUps.erase(powerUps.begin() + power);
			power--;
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

	HUD->render();

	for (int power = 0; power < powerUps.size(); power++)
	{
		powerUps.at(power)->render();
	}

	renderEnemies();

	Jugador.render();

	tm->renderRewards();
}



void WORLD_2_1::refEnemies()
{
	for (int enemy = 0; enemy < mapEnemies.blueEnemies.size(); enemy++)
	{
		mapEnemies.blueEnemies[enemy].setLevelRefrence(2, &_map);
	}

	for (int enemy = 0; enemy < mapEnemies.orangeEnemies.size(); enemy++)
	{
		mapEnemies.orangeEnemies[enemy].setLevelRefrence(2, &_map);
	}
}

void WORLD_2_1::spawnEnemies(int blueQuantity = 2, int orangeQuantity = 0)
{

	mapEnemies.blueEnemies.resize(blueQuantity);
	mapEnemies.orangeEnemies.resize(orangeQuantity);

	for (int enemy = 0; enemy < mapEnemies.blueEnemies.size(); enemy++)
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
				int positionX = ((randX * TILE_SIZE) + (TILE_SIZE / 2) - (mapEnemies.blueEnemies[enemy].getRect().w / 2));
				int positionY = ((randY * TILE_SIZE) + (TILE_SIZE / 2) - (mapEnemies.blueEnemies[enemy].getRect().h / 2)) + INTERFACE_MARGIN;

				mapEnemies.blueEnemies[enemy].setPosition(positionX, positionY);
				spawned = true;
			}
		}
	}

	for (int enemy = 0; enemy < mapEnemies.orangeEnemies.size(); enemy++)
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
				int positionX = ((randX * TILE_SIZE) + (TILE_SIZE / 2) - (mapEnemies.orangeEnemies[enemy].getRect().w / 2));
				int positionY = ((randY * TILE_SIZE) + (TILE_SIZE / 2) - (mapEnemies.orangeEnemies[enemy].getRect().h / 2)) + INTERFACE_MARGIN;

				mapEnemies.orangeEnemies[enemy].setPosition(positionX, positionY);
				spawned = true;
			}
		}
	}
}

void WORLD_2_1::updateEnemies()
{
	for (int enemy = 0; enemy < mapEnemies.blueEnemies.size(); enemy++)
	{
		mapEnemies.blueEnemies[enemy].update();
	}

	for (int enemy = 0; enemy < mapEnemies.orangeEnemies.size(); enemy++)
	{
		mapEnemies.orangeEnemies[enemy].update();
	}
}

void WORLD_2_1::checkEnemies()
{
	for (int enemy = 0; enemy < mapEnemies.blueEnemies.size(); enemy++)
	{
		if (checkEntitiesCollision(Jugador.getRect(), Jugador.getBotY(), mapEnemies.blueEnemies[enemy].getRect(), mapEnemies.blueEnemies[enemy].getBotY()))
		{
			Jugador.setAliveStatus(false);
		}

		if (checkBombCollision(mapEnemies.blueEnemies[enemy].getRect(), mapEnemies.blueEnemies[enemy].getBotY()))
		{
			HUD->addScore(mapEnemies.blueEnemies[enemy].getPoints());
			tm->addReward(mapEnemies.blueEnemies[enemy].getPoints(), mapEnemies.blueEnemies[enemy].getRect(), 255, 255, 255, 255);
			mapEnemies.blueEnemies.erase(mapEnemies.blueEnemies.begin() + enemy);
			enemy--;
		}
	}

	for (int enemy = 0; enemy < mapEnemies.orangeEnemies.size(); enemy++)
	{
		if (checkEntitiesCollision(Jugador.getRect(), Jugador.getBotY(), mapEnemies.orangeEnemies[enemy].getRect(), mapEnemies.orangeEnemies[enemy].getBotY()))
		{
			Jugador.setAliveStatus(false);
		}

		if (checkBombCollision(mapEnemies.orangeEnemies[enemy].getRect(), mapEnemies.orangeEnemies[enemy].getBotY()))
		{
			HUD->addScore(mapEnemies.orangeEnemies[enemy].getPoints());
			tm->addReward(mapEnemies.orangeEnemies[enemy].getPoints(), mapEnemies.orangeEnemies[enemy].getRect(), 255, 255, 255, 255);
			mapEnemies.orangeEnemies.erase(mapEnemies.orangeEnemies.begin() + enemy);
			enemy--;
		}
	}
}

void WORLD_2_1::renderEnemies()
{
	for (int enemy = 0; enemy < mapEnemies.blueEnemies.size(); enemy++)
	{
		mapEnemies.blueEnemies[enemy].render();
	}

	for (int enemy = 0; enemy < mapEnemies.orangeEnemies.size(); enemy++)
	{
		mapEnemies.orangeEnemies[enemy].render();
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

void WORLD_2_1::calculateCamera()
{
	CameraX = (Jugador.getRect().x - SCREEN_WIDTH / 2);

	if (CameraX > _map.getMapWidth() * _map.getTileWidth() - SCREEN_WIDTH)
	{
		CameraX = _map.getMapWidth() * _map.getTileWidth() - SCREEN_WIDTH;
	}

	if (CameraX < 0)
	{
		CameraX = 0;
	}

	_map.setCamera(CameraX);
	Jugador.setCamera(CameraX);
	tm->Camera.x = CameraX;

	for (int enemy = 0; enemy < mapEnemies.blueEnemies.size(); enemy++)
	{
		mapEnemies.blueEnemies[enemy].setCamera(CameraX);
	}

	for (int enemy = 0; enemy < mapEnemies.orangeEnemies.size(); enemy++)
	{
		mapEnemies.orangeEnemies[enemy].setCamera(CameraX);
	}
}

bool WORLD_2_1::checkEntitiesCollision(rect victim, int victimBotY, rect enemy, int enemyBotY)
{
	bool OverlapsX = false, OverlapsY = false;

	if (victim.x + victim.w > enemy.x && enemy.x + enemy.w > victim.x) {
		OverlapsX = true;
	}

	if (victim.y + victim.h > (enemy.y + enemyBotY) && enemy.y + enemy.h > (victim.y + victimBotY)) {
		OverlapsY = true;
	}

	if (OverlapsX && OverlapsY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void WORLD_2_1::generatePowerUp(int x, int y)
{
	x = (x * TILE_SIZE) + (TILE_SIZE / 2) - 16;
	y = (y * TILE_SIZE) + (TILE_SIZE / 2) - 16;

	int actualProbability = rand() % 100;

	if (actualProbability < 50)
	{
		int powerToGen = rand() % powerType::PowerQuantity;

		powerUp* newPower = new powerUp(x, y, powerToGen);

		powerUps.push_back(newPower);

		return;
	}
}
