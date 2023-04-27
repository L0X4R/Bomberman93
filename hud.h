#ifndef HUD_H
#define HUD_H

#include "ResourceManager.h";
#include "TextManager.h"

#define FONT_SIZE 128

class hud
{
private:
	hud();
	static hud* pInstance;

	// MANAGERS
	ResourceManager* rm;
	VideoManager* vm;
	TextManager* tm;

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

	rect timeRect;
	rect scoreRect;
	rect livesRect;

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

	int getScore()
	{
		return score;
	}

	void resetTime();

	void update();

	void render();
};

#endif

