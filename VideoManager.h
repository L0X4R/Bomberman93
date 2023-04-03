#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "config.h"

using namespace std;
#pragma endregion

struct rect
{
	int x;
	int y;
	int w;
	int h;
};

class VideoManager
{
private:
	VideoManager();
	static VideoManager* pInstance;

	SDL_Surface* windowIcon;

	unsigned int lastTime, currentTime, deltaTime;
	float msFrame = 1 / (FRAMERATE / 1000.0f);

public:
	SDL_Window* gWindow;
	SDL_Renderer* GPU;

	string mainTitle;
	float updateCounter = 0;
	float eachUpdate = 1000;

	static VideoManager* getInstance();
	~VideoManager();

	int getProcessTime();

	void createWindow(string Title, int width, int height);
	void updateSubTitle(string Title);
	void renderGraphic(int graphicId, rect graphicRect, rect screenRect);
	void clearScreen(int R, int G, int B, int A);
	void updateScreen();
	float getDeltaTime();
	void drawPoint(int x, int y);
	void drawRect(rect rect);
	int autoWaitTime();
	void waitTime(int ms);
	void close();
};
#endif // !VIDEOMANAGER_H
