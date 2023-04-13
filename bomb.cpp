#include "bomb.h"
#include "player.h"

bomb::bomb(int cellX, int cellY, int bombRange, int _stage, vector<vector<int>>* level, vector<vector<int>>* dyLevel, vector<vector<int>>* collisions)
{
	graphicID = -1;

	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	im = InputManager::getInstance();

	graphicID = rm->loadAndGetGraphicID(graphicPath);

	if (graphicID != -1 && rm != nullptr && vm != nullptr && im != nullptr && level != nullptr && collisions != nullptr)
	{
		levelReference = level;
		dynamicLevelReference = dyLevel;
		availableCollisions = collisions;

		int genPosX = (cellX * TILE_SIZE) + (TILE_SIZE / 2);
		int genPosY = (cellY * TILE_SIZE) + (TILE_SIZE / 2);

		position.x = cellX;
		position.y = cellY;

		thisRect.x = 0;
		thisRect.y = 0;
		thisRect.w = TILE_SIZE;
		thisRect.h = TILE_SIZE;

		worldRect.x = genPosX - (TILE_SIZE / 2);
		worldRect.y = genPosY - (TILE_SIZE / 2);
		worldRect.w = thisRect.w;
		worldRect.h = thisRect.h;

		stage = _stage;

		range = bombRange;

		explotionGraph.resize(4);

		for (int i = 0; i < 4; i++)
		{
			explotionGraph[i].resize(range);
		}

		GOOD("BOMBA PLANTADA.");
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
		rect actualTile;
		rect newTile;
		point cellToCheck;

		for (int dir = 0; dir < explosionDir::ALL; dir++)
		{
			actualTile.x = worldRect.x;
			actualTile.y = worldRect.y;
			actualTile.w = TILE_SIZE;
			actualTile.h = TILE_SIZE;

			switch (dir)
			{
			case UP:
				for (int i = 0; i < range; i++)
				{
					cellToCheck.x = (actualTile.x + (actualTile.w / 2)) / TILE_SIZE;
					cellToCheck.y = ((actualTile.y - INTERFACE_MARGIN + (actualTile.w / 2)) - TILE_SIZE) / TILE_SIZE;

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

					bool dynamicBlock = false;

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						dynamicBlock = true;
						dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x) = 0;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)) || dynamicBlock)
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
					cellToCheck.y = ((actualTile.y - INTERFACE_MARGIN + (actualTile.w / 2)) + TILE_SIZE) / TILE_SIZE;

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

					bool dynamicBlock = false;

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						dynamicBlock = true;
						dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x) = 0;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)) || dynamicBlock)
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
					cellToCheck.y = (actualTile.y - INTERFACE_MARGIN + (actualTile.w / 2)) / TILE_SIZE;

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

					bool dynamicBlock = false;

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						dynamicBlock = true;
						dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x) = 0;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)) || dynamicBlock)
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
					cellToCheck.y = (actualTile.y - INTERFACE_MARGIN + (actualTile.w / 2)) / TILE_SIZE;

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

					bool dynamicBlock = false;

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x)))
					{
						dynamicBlock = true;
						dynamicLevelReference->at(cellToCheck.y).at(cellToCheck.x) = 0;
					}

					if (count(availableCollisions->at(stage - 1).begin(), availableCollisions->at(stage - 1).end(), levelReference->at(cellToCheck.y).at(cellToCheck.x)) || dynamicBlock)
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

	for (int dir = 0; dir < ALL; dir++)
	{
		for (int r = 0; r < range; r++)
		{
			explotionGraph[dir][r].tile.x;
			explotionGraph[dir][r].tile.y;
		}
	}
}

void bomb::render()
{
	rect worldCamPostion = worldRect;

	worldCamPostion.x -= Camera.x;

	if (exploding)
	{
		thisRect.x = TILE_SIZE * 6;
		thisRect.y = TILE_SIZE * 5;

		vm->renderGraphic(graphicID, thisRect, worldCamPostion);

		for (int dir = 0; dir < ALL; dir++)
		{
			for (int r = 0; r < range; r++)
			{
				thisRect.x = explotionGraph[dir][r].offset.x * TILE_SIZE;
				thisRect.y = explotionGraph[dir][r].offset.y * TILE_SIZE;

				rect tileWorldPosition = explotionGraph[dir][r].tile;

				tileWorldPosition.x -= Camera.x;

				vm->renderGraphic(graphicID, thisRect, tileWorldPosition);
			}
		}
	}
	else
	{
		thisRect.x = 0;
		thisRect.y = 0;
		vm->renderGraphic(graphicID, thisRect, worldCamPostion);
	}
}
