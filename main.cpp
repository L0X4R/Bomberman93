#pragma region INCLUDES
#include "VideoManager.h"
#include "SceneManager.h"
#pragma endregion

int main(int argc, char* args[])
{
#pragma region MANAGER SETUP
	// INSTANCIA VIDEO MANAGER + CREACION DE VENTANA.
	VideoManager* WINDOW = VideoManager::getInstance();

	WINDOW->createWindow("BOMBERMAN 93", 1280, 720);

	// INSTANCIA SCENE MANAGER
	SceneManager* SCENE = SceneManager::getInstance();
#pragma endregion

#pragma region INIT
	// MAIN GAME
	bool endProcess = false;
	bool endGame = false;
#pragma endregion

	while (!endProcess)
	{
		while (!endGame)
		{
			#pragma region SCENE RENDER

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