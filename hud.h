#ifndef HUD_H
#define HUD_H

#include "ResourceManager.h";
#include "SDL_TTF.h"

#define FONT_SIZE 128

class hud
{
private:
	hud();
	static hud* pInstance;

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
	SDL_Texture* livesRender;

	SDL_Rect timeRect;
	SDL_Rect scoreRect;
	SDL_Rect livesRect;

	rect thisRect, worldPosition;

	void setRenderTime();
	void setRenderScore();
	void setRenderLives();
	void setRendersPosition();

public:
	~hud();

	static hud* getInstance();

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

#endif

