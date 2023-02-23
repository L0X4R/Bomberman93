#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"

#include <iostream>
#include <map>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "config.h"

using namespace std;
#pragma endregion

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

	static VideoManager* getInstance();
	~VideoManager();

	int getProcessTime();

	void createWindow(const char* Title, int width, int height);
	void renderGraphic(int graphicId, int posX, int posY, int width, int height, int offsetX = 0, int offsetY = 0);
	void clearScreen(int R, int G, int B, int A);
	void updateScreen();
	float getDeltaTime();
	int autoWaitTime();
	void waitTime(int ms);
	void close();
};
#endif // !VIDEOMANAGER_H
