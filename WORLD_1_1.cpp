#include "WORLD_1_1.h"

void WORLD_1_1::render()
{
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

				vm->renderGraphic(tilesetID, rectT.x, rectT.y, rectT.w, rectT.h, rectS.x, rectS.y);
			}
		}
	}


	Jugador.render();
}

void WORLD_1_1::update()
{
	Jugador.update();
}

void WORLD_1_1::loadXMLevel()
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();

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

	Jugador.setLevelRefrence(2, &levelData);
}
