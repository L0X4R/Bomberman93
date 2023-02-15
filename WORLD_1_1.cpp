#include "WORLD_1_1.h"

void WORLD_1_1::render()
{
	Jugador.render();
}

void WORLD_1_1::update()
{
	Jugador.update();
}

void WORLD_1_1::loadXMLevel()
{
	tinyxml2::XMLDocument doc;

	if (doc.LoadFile("assets/maps/level.tmx") != tinyxml2::XML_SUCCESS)
	{
		cout << "ERROR XML: " << doc.ErrorStr();
		ERROR("NO SE HA ENCONTRADO EL ARCHIVO XML.");
		exit(1);
	}

	LOG("CARGANDO DATOS XML DEL NIVEL.");

	tinyxml2::XMLElement* root = doc.FirstChildElement();

	for (tinyxml2::XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement())
	{
		string tag = element->Value();
		string dataLevel = "";

		if (tag == "layer")
		{
			dataLevel = element->FirstChildElement()->GetText();
			break;
		}
	}


}
