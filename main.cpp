#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#pragma endregion

int main(int argc, char* args[])
{
#pragma region MANAGER SETUP
	// INSTANCIA VIDEO MANAGER + CREACION DE VENTANA.
	VideoManager* WINDOW = VideoManager::getInstance();

	WINDOW->createWindow("BOMBERMAN 93", SCREEN_WIDTH, SCREEN_HEIGHT);

	// INSTANCIA RESOURCE MANAGER.
	ResourceManager* RESOURCES = ResourceManager::getInstance();

	// INSTANCIA SCENE MANAGER
	SceneManager* SCENE = SceneManager::getInstance();

	// INSTANCIA INPUT MANAGER
	InputManager* INPUT = InputManager::getInstance();

	SCENE->init();
	SCENE->loadScene(SceneEnum::LEVEL_1_1);
#pragma endregion

#pragma region INIT
	// MAIN GAME
	bool endProcess = false;
	bool endGame = false;

	float updateCounter = 0;
	float eachUpdate = 250;
#pragma endregion

	while (!endProcess)
	{
		while (!endGame)
		{
			INPUT->update();

			if (INPUT->needCloseGame())
			{
				endGame = true;
				endProcess = true;
			}

			SCENE->getLoadedScene()->update();
			SCENE->getLoadedScene()->render();
			WINDOW->updateScreen();
			WINDOW->clearScreen(0, 0, 0, 255);

			#pragma region WAIT TIME AND FPS
			int FPS = WINDOW->autoWaitTime();

			updateCounter += WINDOW->getDeltaTime();

			if (updateCounter >= eachUpdate)
			{
				updateCounter = 0;
				printf("FPS: %d\r", FPS);
			}
			#pragma endregion
		}
	}

	WINDOW->close();
	return 0;
}