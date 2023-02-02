#pragma region INCLUDES
#include <iostream>
#include <windows.h>

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
	// OCULTANDO LA CONSOLA (NO FUNCIONA CON TERMINAL WINDOWS 11).
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// INSTANCIA VIDEO MANAGER + CREACION DE VENTANA.
	VideoManager* WINDOW = VideoManager::getInstance();
	WINDOW->createWindow("BOMBERMAN 93", 1280, 720);

	// INSTANCIA RESOURCE MANAGER.
	ResourceManager* RESOURCES = ResourceManager::getInstance();

	// INSTANCIA AUDIO MANAGER.
	AudioManager* AUDIO = AudioManager::getInstance();

	// INSTANCIA INPUT MANAGER
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
			// CHECK IF INPUT HAS DETECTED.
			inputReturn = INPUT->checkInput();

			// CLOSE PROCESS ON WINDOW_CLOSE INPUT.
			if (inputReturn == InputData::WINDOW_CLOSE)
			{
				endGame = true;
				endProcess = true;
			}

			// DEBUG CONSOLE
			if (inputReturn == InputData::CONSOLE_TOGGLE)
			{
				if (ShowWindow(GetConsoleWindow(), SW_SHOW))
				{
					ShowWindow(GetConsoleWindow(), SW_HIDE);
				}
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