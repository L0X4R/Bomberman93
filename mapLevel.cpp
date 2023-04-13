#include "mapLevel.h"

mapLevel::mapLevel()
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();

	tileMargin = 4;
}

mapLevel::~mapLevel()
{
}

void mapLevel::loadMap(const char* _levelName, const char* mapPath, const char* tilePath)
{
	tilesetID = rm->loadAndGetGraphicID(tilePath);

	tinyxml2::XMLDocument doc;

	if (doc.LoadFile(mapPath) != tinyxml2::XML_SUCCESS)
	{
		cout << "ERROR XML: " << doc.ErrorStr();
		ERROR("NO SE HA ENCONTRADO EL ARCHIVO XML.");
		exit(1);
	}

	LOG("CARGANDO INFORMACION DEL MAPA [" << _levelName << "]...");

	tinyxml2::XMLElement* root = doc.FirstChildElement();

	levelName = _levelName;
	mapWidth = stoi(root->Attribute("width"));
	mapHeight = stoi(root->Attribute("height"));
	tileWidth = stoi(root->Attribute("tilewidth"));
	tileHeight = stoi(root->Attribute("tileheight"));

	for (tinyxml2::XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement())
	{
		string tag = element->Value();

		if (tag == "layer")
		{
			string attr = element->Attribute("name");

			if (attr == "staticMap")
			{
				string dataLevel = element->FirstChildElement()->GetText();
				stringstream iss(dataLevel);

				int row = 0;
				staticMap.resize(1);

				for (int i; iss >> i;) {
					staticMap[row].push_back(i);
					if (iss.peek() == ',')
						iss.ignore();

					if (iss.peek() == '\n')
					{
						row++;
						if (row != mapWidth)
						{
							staticMap.resize(row + 1);
						}
					}

				}
			}
			else if (attr == "dynamicMap")
			{
				string dataLevel = element->FirstChildElement()->GetText();
				stringstream iss(dataLevel);

				int row = 0;
				dynamicMap.resize(1);

				for (int i; iss >> i;) {
					dynamicMap[row].push_back(i);
					if (iss.peek() == ',')
						iss.ignore();

					if (iss.peek() == '\n')
					{
						row++;
						if (row != mapWidth)
						{
							dynamicMap.resize(row + 1);
						}
					}

				}
			}
		}
	}

	GOOD("INFORMACION DEL MAPA CARGADA.");
}

void mapLevel::render()
{
	int tileID, cellX, cellY;

	int InitX = Camera.x / tileWidth;
	int LastX = (2 + SCREEN_WIDTH / tileWidth) + InitX;

	if (LastX > mapWidth)
	{
		LastX = mapWidth;
	}

	// RENDER ALL TILE OF MAP.
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = InitX; x < LastX; x++)
		{
			rectT.x = x * tileWidth;
			rectT.y = y * tileHeight + INTERFACE_MARGIN;
			rectT.w = tileWidth;
			rectT.h = tileHeight;

			tileID = staticMap[y][x] - 1;

			if (tileID >= 0)
			{
				cellX = tileID % 8;
				cellY = tileID / 8;
				rectS.x = cellX * tileWidth + tileMargin * cellX;
				rectS.y = cellY * tileWidth + tileMargin * cellY;
				rectS.w = tileWidth;
				rectS.h = tileHeight;
				rectT.x -= Camera.x;

				vm->renderGraphic(tilesetID, rectS, rectT);
			}

			tileID = dynamicMap[y][x] - 1;

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
}
