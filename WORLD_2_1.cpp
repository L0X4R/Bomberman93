#include "WORLD_2_1.h"

void WORLD_2_1::render()
{
	// RENDER ALL TILE OF MAP.
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			rectT.x = x * tileWidth;
			rectT.y = y * tileHeight;
			rectT.w = tileWidth;
			rectT.h = tileHeight;

			tileID = levelData[y][x] - 1;

			if (tileID >= 0)
			{
				cellX = tileID % 8;
				cellY = tileID / 8;
				rectS.x = cellX * tileWidth + tileMargin * cellX;
				rectS.y = cellY * tileWidth + tileMargin * cellY;
				rectS.w = tileWidth;
				rectS.h = tileHeight;

				vm->renderGraphic(tilesetID, rectS, rectT);
			}
		}
	}

	for (int bomb = 0; bomb < Jugador.getBombs()->size(); bomb++)
	{
		Jugador.getBombs()->at(bomb)->render();
	}

	Jugador.render();
}

void WORLD_2_1::update()
{
	Jugador.update();
	
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

// LOAD XML MAP.
void WORLD_2_1::loadXMLevel()
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();

	if (isGameArea)
	{
		tilesetID = rm->loadAndGetGraphicID(tilesetPath);

		tinyxml2::XMLDocument doc;

		if (doc.LoadFile(levelPath) != tinyxml2::XML_SUCCESS)
		{
			cout << "ERROR XML: " << doc.ErrorStr();
			ERROR("NO SE HA ENCONTRADO EL ARCHIVO XML.");
			exit(1);
		}

		LOG("CARGANDO INFORMACION DEL MAPA [" << levelName << "]...");

		tinyxml2::XMLElement* root = doc.FirstChildElement();

		for (tinyxml2::XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement())
		{
			string tag = element->Value();

			if (tag == "layer")
			{
				string dataLevel = element->FirstChildElement()->GetText();
				stringstream iss(dataLevel);

				int row = 0;
				levelData.resize(1);

				for (int i; iss >> i;) {
					levelData[row].push_back(i);
					if (iss.peek() == ',')
						iss.ignore();

					if (iss.peek() == '\n')
					{
						row++;
						if (row != mapHeight)
						{
							levelData.resize(row + 1);
						}
					}

				}

				GOOD("INFORMACION DEL MAPA CARGADA.");
				break;
			}
		}

		// SET LEVEL REFERENCES AND STAGE NUMBER.
		Jugador.setLevelRefrence(2, &levelData);
	}
}
