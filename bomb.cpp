#include "bomb.h"

bomb::bomb(int cellX, int cellY, int bombRange, int _stage, vector<vector<int>>* level, vector<vector<int>>* collisions)
{
	graphicID = -1;

	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	im = InputManager::getInstance();

	LOG("CREANDO BOMBA...");

	graphicID = rm->loadAndGetGraphicID(graphicPath);

	if (graphicID != -1 && rm != nullptr && vm != nullptr && im != nullptr && level != nullptr && collisions != nullptr)
	{
		levelReference = level;
		availableCollisions = collisions;

		int genPosX = (cellX * TILE_SIZE) + (TILE_SIZE / 2);
		int genPosY = (cellY * TILE_SIZE) + (TILE_SIZE / 2);

		position.x = cellX;
		position.y = cellY;

		objectRect.x = genPosX - (TILE_SIZE / 2);
		objectRect.y = genPosY - (TILE_SIZE / 2);

		objectRect.w = TILE_SIZE;
		objectRect.h = TILE_SIZE;

		stage = _stage;

		range = bombRange;

		explotionGraph.resize(4);

		for (int i = 0; i < 4; i++)
		{
			explotionGraph[i].resize(range);
		}

		GOOD("LA BOMBA SE HA CREADO CON EXITO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CREAR LA BOMBA.");
		exit(1);
	}
}

bomb::~bomb()
{
}

void bomb::generateExplosion()
{
	if (levelReference != nullptr)
	{
		objRect actualTile;
		objRect newTile;
		point cellToCheck;

		for (int dir = 0; dir < explosionDir::ALL; dir++)
		{
			actualTile.x = objectRect.x;
			actualTile.y = objectRect.y;
			actualTile.w = TILE_SIZE;
			actualTile.h = TILE_SIZE;

			switch (dir)
			{
			case UP:
				for (int i = 0; i < range; i++)
				{
					cellToCheck.x = (actualTile.x + (actualTile.w / 2)) / TILE_SIZE;
					cellToCheck.y = ((actualTile.y + (actualTile.w / 2)) - TILE_SIZE) / TILE_SIZE;

					newTile.x = actualTile.x;
					newTile.y = actualTile.y - TILE_SIZE;
					newTile.w = TILE_SIZE;
					newTile.h = TILE_SIZE;

					point offset;

					if (i == (range - 1))
					{
						offset.x = 0;
						offset.y = 5;
					}
					else
					{
						offset.x = 4;
						offset.y = 5;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						offset.x = 0;
						offset.y = 5;

						if (i > 0)
						{
							explotionGraph[UP][i - 1].offset = offset;
						}
						break;
					}
					else
					{
						explosionTile newCellTile;

						newCellTile.tile = newTile;
						newCellTile.offset = offset;

						explotionGraph[UP][i] = newCellTile;
						actualTile.y -= TILE_SIZE;
					}
				}
				break;
			case DOWN:
				for (int i = 0; i < range; i++)
				{
					cellToCheck.x = (actualTile.x + (actualTile.w / 2)) / TILE_SIZE;
					cellToCheck.y = ((actualTile.y + (actualTile.w / 2)) + TILE_SIZE) / TILE_SIZE;

					newTile.x = actualTile.x;
					newTile.y = actualTile.y + TILE_SIZE;
					newTile.w = TILE_SIZE;
					newTile.h = TILE_SIZE;

					point offset;

					if (i == (range - 1))
					{
						offset.x = 1;
						offset.y = 5;
					}
					else
					{
						offset.x = 4;
						offset.y = 5;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						offset.x = 1;
						offset.y = 5;

						if (i > 0)
						{
							explotionGraph[DOWN][i - 1].offset = offset;
						}
						break;
					}
					else
					{
						explosionTile newCellTile;

						newCellTile.tile = newTile;
						newCellTile.offset = offset;

						explotionGraph[DOWN][i] = newCellTile;
						actualTile.y += TILE_SIZE;
					}
				}
				break;
			case LEFT:
				for (int i = 0; i < range; i++)
				{
					cellToCheck.x = (actualTile.x + (actualTile.w / 2) - TILE_SIZE) / TILE_SIZE;
					cellToCheck.y = (actualTile.y + (actualTile.w / 2)) / TILE_SIZE;

					newTile.x = actualTile.x - TILE_SIZE;
					newTile.y = actualTile.y;
					newTile.w = TILE_SIZE;
					newTile.h = TILE_SIZE;

					point offset;

					if (i == (range - 1))
					{
						offset.x = 2;
						offset.y = 5;
					}
					else
					{
						offset.x = 5;
						offset.y = 5;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						offset.x = 2;
						offset.y = 5;

						if (i > 0)
						{
							explotionGraph[LEFT][i - 1].offset = offset;
						}
						break;
					}
					else
					{
						explosionTile newCellTile;

						newCellTile.tile = newTile;
						newCellTile.offset = offset;

						explotionGraph[LEFT][i] = newCellTile;
						actualTile.x -= TILE_SIZE;
					}
				}
				break;
			case RIGHT:
				for (int i = 0; i < range; i++)
				{
					cellToCheck.x = (actualTile.x + (actualTile.w / 2) + TILE_SIZE) / TILE_SIZE;
					cellToCheck.y = (actualTile.y + (actualTile.w / 2)) / TILE_SIZE;

					newTile.x = actualTile.x + TILE_SIZE;
					newTile.y = actualTile.y;
					newTile.w = TILE_SIZE;
					newTile.h = TILE_SIZE;

					point offset;

					if (i == (range - 1))
					{
						offset.x = 3;
						offset.y = 5;
					}
					else
					{
						offset.x = 5;
						offset.y = 5;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						offset.x = 3;
						offset.y = 5;

						if (i > 0)
						{
							explotionGraph[RIGHT][i - 1].offset = offset;
						}
						break;
					}
					else
					{
						explosionTile newCellTile;

						newCellTile.tile = newTile;
						newCellTile.offset = offset;

						explotionGraph[RIGHT][i] = newCellTile;
						actualTile.x += TILE_SIZE;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	exploding = true;
}

void bomb::update()
{
	bombTime += vm->getDeltaTime();

	if (bombTime >= explodeTime && exploding == false)
	{
		generateExplosion();
		bombTime = 0;
	}

	if (exploding == true && bombTime >= explodeTime)
	{
		exploded = true;
	}

	if (exploded)
	{
		LOG("LA BOMBA HA EXPLOTADO!");
	}
}

void bomb::render()
{
	vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, 0, 0);

	if (exploding)
	{
		vm->renderGraphic(graphicID, objectRect.x, objectRect.y, objectRect.w, objectRect.h, TILE_SIZE * 6, TILE_SIZE * 5);

		for (int dir = 0; dir < ALL; dir++)
		{
			for (int r = 0; r < range; r++)
			{
				vm->renderGraphic(graphicID, explotionGraph[dir][r].tile.x, explotionGraph[dir][r].tile.y, explotionGraph[dir][r].tile.w, explotionGraph[dir][r].tile.h, explotionGraph[dir][r].offset.x * TILE_SIZE, explotionGraph[dir][r].offset.y * TILE_SIZE);
			}
		}
	}
}
