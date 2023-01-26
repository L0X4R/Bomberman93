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
	LOG("CREANDO GESTOR DE ENTRADA.")
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
			return InputData::WINDOW_CLOSE;
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return InputData::WINDOW_CLOSE;

			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				return InputData::W_DOWN;

			if (event.key.keysym.scancode == SDL_SCANCODE_S)
				return InputData::S_DOWN;

			if (event.key.keysym.scancode == SDL_SCANCODE_A)
				return InputData::A_DOWN;

			if (event.key.keysym.scancode == SDL_SCANCODE_D)
				return InputData::D_DOWN;

		case SDL_KEYUP:
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				return InputData::W_UP;

			if (event.key.keysym.scancode == SDL_SCANCODE_S)
				return InputData::S_UP;

			if (event.key.keysym.scancode == SDL_SCANCODE_A)
				return InputData::A_UP;

			if (event.key.keysym.scancode == SDL_SCANCODE_D)
				return InputData::D_UP;
		default:
			return -1;
		}
	}
}
