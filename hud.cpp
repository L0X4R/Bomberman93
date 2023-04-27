#include "hud.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

hud* hud::pInstance = NULL;

hud::hud()
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	tm = TextManager::getInstance();

	lives = 0;
	score = 0;
	bestScore = 0;
	playedMin = 0;
	playedSec = 0;

	LOG("CARGANDO EL HUD...");
	graphicID = rm->loadAndGetGraphicID(graphicPath);

	thisRect.x = 0;
	thisRect.y = 0;
	thisRect.w = SCREEN_WIDTH;
	thisRect.h = 64;

	worldPosition = thisRect;

	setRendersPosition();

	if (graphicID != -1 || rm != nullptr || vm != nullptr)
	{
		GOOD("HUD CARGADO CON EXITO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CARGAR EL HUD.");
		exit(1);
	}
}

void hud::setRendersPosition()
{
	timeRect.x = 418;
	timeRect.y = 16;
	timeRect.w = 135;
	timeRect.h = 32;

	scoreRect.x = 161;
	scoreRect.y = 16;
	scoreRect.w = 233;
	scoreRect.h = 32;

	livesRect.x = 1187;
	livesRect.y = 16;
	livesRect.w = 57;
	livesRect.h = 32;
}

hud* hud::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new hud();

	return pInstance;
}

hud::~hud()
{
}

void hud::resetTime()
{
	miliseconds = 0;
	playedSec = 0;
	playedMin = 0;
}

void hud::update()
{
	miliseconds += vm->getDeltaTime();

	if (miliseconds >= 1000)
	{
		miliseconds = 0;
		playedSec += 1;
	}

	if (playedSec >= 60)
	{
		playedSec = 0;
		playedMin += 1;
	}
}

void hud::render()
{
	vm->renderGraphic(graphicID, thisRect, worldPosition);

	setRenderTime();
	setRenderScore();
	setRenderLives();
}

void hud::setRenderTime()
{
	string seconds;
	string minutes;

	if (playedSec <= 9)
	{
		seconds = "0" + to_string(playedSec);
	}
	else
	{
		seconds = to_string(playedSec);
	}

	if (playedMin <= 9)
	{
		minutes = "0" + to_string(playedMin);
	}
	else
	{
		minutes = to_string(playedMin);
	}

	string stringTime = minutes + ":" + seconds;

	tm->DrawText(stringTime, timeRect, 255, 255, 255, 255);
}

void hud::setRenderScore()
{
	stringstream formatedScore;

	formatedScore << setw(10) << setfill('0') << score;

	tm->DrawText(formatedScore.str(), scoreRect, 255, 255, 255, 255);
}

void hud::setRenderLives()
{
	tm->DrawText(to_string(lives), livesRect, 255, 255, 255, 255);
}
