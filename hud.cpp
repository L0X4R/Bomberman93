#include "hud.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

hud::hud()
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();

	lives = 0;

	score = 0;
	bestScore = 0;

	playedMin = 0;
	playedSec = 0;

	LOG("CARGANDO EL HUD...");
	graphicID = rm->loadAndGetGraphicID(graphicPath);

	font = TTF_OpenFont("assets/unispace.ttf", FONT_SIZE);
	fontColor = { 255, 255, 255 };

	thisRect.x = 0;
	thisRect.y = 0;
	thisRect.w = SCREEN_WIDTH;
	thisRect.h = 64;

	worldPosition = thisRect;

	timeRect.x = 418;
	timeRect.y = 16;
	timeRect.w = 135;
	timeRect.h = 32;

	scoreRect.x = 161;
	scoreRect.y = 16;
	scoreRect.w = 233;
	scoreRect.h = 32;

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

hud::~hud()
{
}

void hud::update()
{
	miliseconds += vm->getDeltaTime();

	if (miliseconds >= 1000)
	{
		miliseconds = 0;
		playedSec += 1;

		// TEST SCORE
		addScore(999);
	}

	if (playedSec >= 60)
	{
		playedSec = 0;
		playedMin += 1;
	}

	setRenderTime();

	// PROBLEMA DE RENDIMIENTO [DEMASIADA RAM]
	//setRenderScore();
}

void hud::render()
{
	vm->renderGraphic(graphicID, thisRect, worldPosition);

	SDL_RenderCopy(vm->GPU, timeRender, NULL, &timeRect);
	SDL_RenderCopy(vm->GPU, scoreRender, NULL, &scoreRect);

	SDL_FreeSurface(fontSurface);
	SDL_DestroyTexture(timeRender);
	SDL_DestroyTexture(scoreRender);
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

	fontSurface = TTF_RenderText_Solid(font, stringTime.c_str(), fontColor);
	timeRender = SDL_CreateTextureFromSurface(vm->GPU, fontSurface);
}

void hud::setRenderScore()
{
	stringstream* formatedScore = new stringstream;

	*formatedScore << setw(10) << setfill('0') << score;

	fontSurface = TTF_RenderText_Solid(font, formatedScore->str().c_str(), fontColor);
	scoreRender = SDL_CreateTextureFromSurface(vm->GPU, fontSurface);

	formatedScore->clear();
	delete formatedScore;
	formatedScore = nullptr;
}
