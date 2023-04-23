#include "WORLD_2_1.h"

void WORLD_2_1::initLevel()
{
	rm = ResourceManager::getInstance();
	am = AudioManager::getInstance();

	backgroundMusic = rm->loadAndGetSoundID("assets/sounds/bgMusic.mp3");
	impactSound =  rm->loadAndGetSoundID("assets/sounds/impact.wav");
	levelCompleteSound = rm->loadAndGetSoundID("assets/sounds/levelComplete.wav");
	pickUpSound = rm->loadAndGetSoundID("assets/sounds/pickUp.wav");

	srand(time(NULL));

	_map.loadMap("LEVEL 2-1", "assets/maps/s2m1.tmx", "assets/maps/ice.png");

	Jugador.setLevelRefrence(2, &_map);

	spawnEnemies(15);

	// SET MAP REFERENCE TO ENEMIES
	for (int enemy = 0; enemy < enemies.size(); enemy++)
	{
		enemies[enemy]->setLevelRefrence(2, &_map);
	}

	CameraX = 0;

	HUD = hud::getInstance();
	tm = TextManager::getInstance();

	am->playSound(-1, backgroundMusic, 25, true);
}

void WORLD_2_1::update()
{
	// PLAYER UPDATE
	Jugador.update();

	// UPDATE ENEMIES AND CHECK COLLISIONS
	for (int enemy = 0; enemy < enemies.size(); enemy++)
	{
		// UPDATE ENEMIES
		enemies[enemy]->update();

		// CHECK IF PLAYER COLLISION WITH ENEMY
		if (checkEntitiesCollision(Jugador.getRect(), Jugador.getBotY(), enemies[enemy]->getRect(), enemies[enemy]->getBotY()))
		{
			Jugador.setAliveStatus(false);
		}

		// CHECK IF BOMB COLLISION WITH ENEMY
		if (checkBombCollision(enemies[enemy]->getRect(), enemies[enemy]->getBotY()))
		{
			HUD->addScore(enemies[enemy]->getPoints());
			tm->addReward(enemies[enemy]->getPoints(), enemies[enemy]->getRect(), 255, 255, 255, 255);
			enemies.erase(enemies.begin() + enemy);
			am->playSound(-1, impactSound, 45, false);
			enemy--;
		}
	}

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

	// UPDATE HUD LIVES
	HUD->setLives(Jugador.getLives());

	// UPDATE HUD
	HUD->update();

	// UPDATE POWER UPS
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

	// CHECK POWER UPS COLLISION
	for (int power = 0; power < powerUps.size(); power++)
	{
		powerUps.at(power)->setCamera(CameraX);

		if (checkEntitiesCollision(Jugador.getRect(), Jugador.getBotY(), powerUps.at(power)->getRect(), 0))
		{
			am->playSound(-1, pickUpSound, 30, false);
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

	for (int enemy = 0; enemy < enemies.size(); enemy++)
	{
		enemies[enemy]->render();
	}

	Jugador.render();

	tm->renderRewards();
}

void WORLD_2_1::spawnEnemies(int quantity)
{
	enemies.resize(quantity);

	for (int i = 0; i < quantity; i++)
	{
		bool spawned = false;

		int newType = rand() % 5;

		while (!spawned)
		{
			int randX = rand() % _map.getMapWidth();
			int randY = rand() % _map.getMapHeight();

			int dyTile = _map.getDynamicMap()->at(randY).at(randX);
			int stTile = _map.getStaticMap()->at(randY).at(randX);

			if ((dyTile == 0 && stTile == 3) && ((randX > 2) && (randY > 2)))
			{
				enemy* newEnemy = new enemy(newType);

				int positionX = ((randX * TILE_SIZE) + (TILE_SIZE / 2) - (newEnemy->getRect().w / 2));
				int positionY = ((randY * TILE_SIZE) + (TILE_SIZE / 2) - (newEnemy->getRect().h / 2)) + INTERFACE_MARGIN;

				newEnemy->setPosition(positionX, positionY);

				enemies[i] = newEnemy;

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

		if (Jugador.getBombs()->at(bomb)->isExploding())
		{
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
	// CALCULATE CAMERA POSITION RESPECT PLAYER
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

	// UPDATE CAMERA OF TEXT MANAGER
	tm->Camera.x = CameraX;

	// SET CAMERAS TO ENEMIES
	for (int enemy = 0; enemy < enemies.size(); enemy++)
	{
		enemies[enemy]->setCamera(CameraX);
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

	// SPAWN POWER UP 10% PROBABILITY
	if (actualProbability < 10)
	{
		int powerToGen = rand() % powerType::PowerQuantity;

		powerUp* newPower = new powerUp(x, y, powerToGen);

		powerUps.push_back(newPower);

		return;
	}
}
