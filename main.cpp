#pragma region INCLUDES
#include <iostream>

#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "InputManager.h"

using namespace std;
#pragma endregion

int main(int argc, char* args[])
{
#pragma region MANAGER SETUP
	VideoManager* WINDOW = VideoManager::getInstance();
	WINDOW->createWindow("BOMBERMAN 93", 1280, 720);

	ResourceManager* RESOURCES = ResourceManager::getInstance();

	AudioManager* AUDIO = AudioManager::getInstance();

	InputManager* INPUT = InputManager::getInstance();
#pragma endregion
	bool endProcess = false;
	bool endGame = false;

	while (!endProcess)
	{
		while (!endGame)
		{
			#pragma region UPDATE

			#pragma endregion

			#pragma region RENDER

			#pragma endregion
		}

		WINDOW->updateScreen();
		WINDOW->clearScreen(0, 0, 0, 255);

#pragma region WAIT TIME AND FPS
		int FPS = WINDOW->autoWaitTime();

		if ((WINDOW->getProcessTime() % 1000) <= 10)
		{
			printf("FPS: %d\r", FPS);
		}
#pragma endregion
	}

	WINDOW->close();

	return 0;
}