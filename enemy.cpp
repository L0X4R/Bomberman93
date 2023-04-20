#include "enemy.h"

#define MARGIN_X 10

enemy::enemy(int newType)
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();

	graphicID = rm->loadAndGetGraphicID(graphicPath);

	CollisionPoints.resize(CollisionPoint::ALL_POINTS);

	if (graphicID != -1 && rm != nullptr && vm != nullptr)
	{
		thisRect.x = 0;
		thisRect.y = 0;
		thisRect.w = 48;
		thisRect.h = 48;

		setBotY(30);

		worldRect.x = TILE_SIZE;
		worldRect.y = TILE_SIZE + INTERFACE_MARGIN;
		worldRect.w = thisRect.w;
		worldRect.h = thisRect.h;

		type = newType;

		GOOD("ENEMIGO INSTANCIADO!");
	}
	else
	{
		ERROR("NO SE HA PODIDO INSTANCIAR AL ENEMIGO.");
		exit(1);
	}
}

enemy::~enemy()
{
}

void enemy::update()
{
	frameTime += vm->getDeltaTime();
	moveTime += vm->getDeltaTime();

	lastX = worldRect.x;
	lastY = worldRect.y;

	cellX = (worldRect.x + (worldRect.w / 2)) / TILE_SIZE;
	cellY = (worldRect.y + bot_y) / TILE_SIZE;

	if (type == enemyType::Bat)
	{
		eachTime = 100;
	}
	else
	{
		eachTime = 250;
	}

	if (moveTime >= changeDirIn)
	{
		moveTime = 0;

		actualDirection = rand() % 4;
	}

	switch (type)
	{
	case Slime:
		slime();
		break;
	case Pou:
		pou();
		break;
	case Wazowski:
		wazowski();
		break;
	case Bat:
		bat();
		break;
	case Bloon:
		bloon();
		break;
	default:
		break;
	}

	limitToScreen();

	setCollisionPoints();

	checkTileCollision();
}

void enemy::render()
{
	rect worldCamPostion = worldRect;

	worldCamPostion.x -= Camera.x;

	if (frameTime >= eachTime)
	{
		frameTime = 0;
		frame++;
	}

	if (frame >= maxFrame)
	{
		frame = 0;
	}

	thisRect.x = (frame * thisRect.w);

	if (type == enemyType::Bat)
	{
		thisRect.y = (verticalFrame * thisRect.h);
	}
	else
	{
		thisRect.y = (type * thisRect.h);
	}

	vm->renderGraphic(graphicID, thisRect, worldCamPostion);

	//for (int i = 0; i < CollisionPoints.size(); i++)
	//{
	//	rect temp;

	//	temp.x = CollisionPoints[i].x;
	//	temp.y = CollisionPoints[i].y;

	//	temp.w = 2;
	//	temp.h = 2;

	//	vm->drawRect(temp);
	//}
}

void enemy::setCollisionPoints()
{
	CollisionPoints[TOP_LEFT].x = worldRect.x + MARGIN_X;
	CollisionPoints[TOP_LEFT].y = worldRect.y + bot_y;

	CollisionPoints[TOP_RIGHT].x = worldRect.x + worldRect.w - MARGIN_X;
	CollisionPoints[TOP_RIGHT].y = worldRect.y + bot_y;

	CollisionPoints[RIGHT_TOP].x = worldRect.x + worldRect.w;
	CollisionPoints[RIGHT_TOP].y = worldRect.y + bot_y + 5;

	CollisionPoints[RIGHT_BOTTOM].x = worldRect.x + worldRect.w;
	CollisionPoints[RIGHT_BOTTOM].y = worldRect.y + worldRect.h - 5;

	CollisionPoints[BOTTOM_LEFT].x = worldRect.x + MARGIN_X;
	CollisionPoints[BOTTOM_LEFT].y = worldRect.y + worldRect.h;

	CollisionPoints[BOTTOM_RIGHT].x = worldRect.x + worldRect.w - MARGIN_X;
	CollisionPoints[BOTTOM_RIGHT].y = worldRect.y + worldRect.h;

	CollisionPoints[LEFT_TOP].x = worldRect.x;
	CollisionPoints[LEFT_TOP].y = worldRect.y + bot_y + 5;

	CollisionPoints[LEFT_BOTTOM].x = worldRect.x;
	CollisionPoints[LEFT_BOTTOM].y = worldRect.y + worldRect.h - 5;
}

void enemy::checkTileCollision()
{
	if (map != nullptr)
	{
		rect tempTile;

		int xLimit;
		int yLimit;

		// LIMIT CELL TO CHECK [OPTIMIZATION] (300 loops => 25 loops)
		if (cellX < (map->getMapWidth() + 4))
		{
			xLimit = cellX + 4;
		}
		else
		{
			xLimit = cellX;
		}

		if (cellY < (map->getMapHeight() + 4))
		{
			yLimit = cellY + 4;
		}
		else
		{
			yLimit = cellY;
		}

		for (int y = cellY - 1; y < yLimit; y++)
		{
			for (int x = cellX - 1; x < xLimit; x++)
			{
				tempTile.x = x * 64;
				tempTile.y = y * 64 + INTERFACE_MARGIN;
				tempTile.w = 64;
				tempTile.h = 64;

				for (int cPoint = 0; cPoint < CollisionPoints.size(); cPoint++)
				{
					if (type == enemyType::Bat || type == enemyType::Bloon)
					{
						if (CheckCollision(tempTile, CollisionPoints[cPoint]) && count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), map->getStaticMap()->at(y).at(x)))
						{

							if (cPoint == TOP_LEFT || cPoint == TOP_RIGHT || cPoint == BOTTOM_LEFT || cPoint == BOTTOM_RIGHT)
							{
								worldRect.y = lastY;
							}

							if (cPoint == RIGHT_TOP || cPoint == RIGHT_BOTTOM || cPoint == LEFT_TOP || cPoint == LEFT_BOTTOM)
							{
								worldRect.x = lastX;
							}
						}
					}
					else
					{
						if (CheckCollision(tempTile, CollisionPoints[cPoint]) && (count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), map->getStaticMap()->at(y).at(x)) || count(availableCollisions[stageToCheck - 1].begin(), availableCollisions[stageToCheck - 1].end(), map->getDynamicMap()->at(y).at(x))))
						{

							if (cPoint == TOP_LEFT || cPoint == TOP_RIGHT || cPoint == BOTTOM_LEFT || cPoint == BOTTOM_RIGHT)
							{
								worldRect.y = lastY;
							}

							if (cPoint == RIGHT_TOP || cPoint == RIGHT_BOTTOM || cPoint == LEFT_TOP || cPoint == LEFT_BOTTOM)
							{
								worldRect.x = lastX;
							}
						}
					}
				}
			}
		}
	}
}

void enemy::limitToScreen()
{
	if (worldRect.x < 0)
	{
		worldRect.x = 0;
	}

	if ((worldRect.x + worldRect.w) > map->getMapWidth() * map->getTileWidth())
	{
		worldRect.x = SCREEN_WIDTH - (map->getMapWidth() * map->getTileWidth());
	}

	if (worldRect.y < 0)
	{
		worldRect.y = 0;
	}

	if ((worldRect.y + worldRect.h) > map->getMapHeight() * map->getTileHeight())
	{
		worldRect.y = SCREEN_HEIGHT - (map->getMapHeight() * map->getTileHeight());
	}
}


// ########################################### ENEMIES LOGICS ###########################################

void enemy::slime()
{
	switch (actualDirection)
	{
	case DIR_MOVE::UP:
		worldRect.y -= speed;
		break;
	case DIR_MOVE::DOWN:
		worldRect.y += speed;
		break;
	case DIR_MOVE::LEFT:
		worldRect.x -= speed;
		break;
	case DIR_MOVE::RIGHT:
		worldRect.x += speed;
		break;
	default:
		break;
	}
}

void enemy::pou()
{
	switch (actualDirection)
	{
	case DIR_MOVE::UP:
		worldRect.y -= speed;
		break;
	case DIR_MOVE::DOWN:
		worldRect.y += speed;
		break;
	case DIR_MOVE::LEFT:
		worldRect.x -= speed;
		break;
	case DIR_MOVE::RIGHT:
		worldRect.x += speed;
		break;
	default:
		break;
	}
}

void enemy::wazowski()
{
	switch (actualDirection)
	{
	case DIR_MOVE::UP:
		worldRect.y -= speed;
		break;
	case DIR_MOVE::DOWN:
		worldRect.y += speed;
		break;
	case DIR_MOVE::LEFT:
		worldRect.x -= speed;
		break;
	case DIR_MOVE::RIGHT:
		worldRect.x += speed;
		break;
	default:
		break;
	}
}

void enemy::bat()
{
	switch (actualDirection)
	{
	case DIR_MOVE::UP:
		worldRect.y -= speed;
		verticalFrame = 7;
		break;
	case DIR_MOVE::DOWN:
		worldRect.y += speed;
		verticalFrame = 4;
		break;
	case DIR_MOVE::LEFT:
		worldRect.x -= speed;
		verticalFrame = 5;
		break;
	case DIR_MOVE::RIGHT:
		worldRect.x += speed;
		verticalFrame = 6;
		break;
	default:
		break;
	}
}

void enemy::bloon()
{
	switch (actualDirection)
	{
	case DIR_MOVE::UP:
		worldRect.y -= speed;
		break;
	case DIR_MOVE::DOWN:
		worldRect.y += speed;
		break;
	case DIR_MOVE::LEFT:
		worldRect.x -= speed;
		break;
	case DIR_MOVE::RIGHT:
		worldRect.x += speed;
		break;
	default:
		break;
	}
}