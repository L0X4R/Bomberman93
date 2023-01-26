#pragma region INCLUDES
#include <iostream>

#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "InputManager.h"

#include "player.h"

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

#pragma region INIT

	// MAIN GAME
	bool endProcess = false;
	bool endGame = false;
	int inputReturn;

	// OBJECTS
	player Player;
	position playerPosition;

#pragma endregion

	while (!endProcess)
	{
		while (!endGame)
		{
			#pragma region UPDATE
			inputReturn = INPUT->checkInput();

			if (inputReturn == InputData::WINDOW_CLOSE)
			{
				endGame = true;
				endProcess = true;
			}

			#pragma endregion

			#pragma region RENDER
			Player.render();

			WINDOW->updateScreen();
			WINDOW->clearScreen(0, 0, 0, 255);
			#pragma endregion

			#pragma region WAIT TIME AND FPS
			int FPS = WINDOW->autoWaitTime();

			if ((WINDOW->getProcessTime() % 1000) <= 10)
			{
				printf("FPS: %d\r", FPS);
			}
			#pragma endregion
		}
	}

	WINDOW->close();
	return 0;
}