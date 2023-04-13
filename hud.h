#pragma once
#include "ResourceManager.h";
#include "SDL_TTF.h"

#define FONT_SIZE 128

class hud
{
private:
	// MANAGERS
	ResourceManager* rm;
	VideoManager* vm;

	// GRAPHICS
	const char* graphicPath = "assets/hud.png";
	int graphicID;

	// VALUES
	int lives;

	int score;
	int bestScore;

	int miliseconds;
	int playedMin;
	int playedSec;

	//FONTS
	const char* fontPath = "assets/unispace.ttf";
	TTF_Font* font;
	SDL_Color fontColor;
	SDL_Surface* fontSurface;

	SDL_Texture* timeRender;
	SDL_Texture* scoreRender;

	SDL_Rect timeRect;
	SDL_Rect scoreRect;

	rect thisRect, worldPosition;

	void setRenderTime();
	void setRenderScore();

public:
	hud();
	~hud();

	void setLives(int newLives)
	{
		lives = newLives;
	}

	void setScore(int newScore)
	{
		score = newScore;
	}

	void addScore(int quantity)
	{
		score += quantity;
	}

	void update();

	void render();


};

