#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "InputManager.h"

#include <iostream>;
#include <map>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "config.h"

using namespace std;
#pragma endregion

InputManager* InputManager::pInstance = NULL;

InputManager::InputManager()
{
}

InputManager* InputManager::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new InputManager();

	return pInstance;
}

InputManager::~InputManager()
{
}

int InputManager::checkInput()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			stopProcess = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				stopProcess = true;
			break;
		default:
			break;
		}
	}
}
