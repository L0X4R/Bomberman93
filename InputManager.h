#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "InputManager.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "config.h"
using namespace std;
#pragma endregion

enum InputData
{
	W_UP, W_DOWN,
	S_UP, S_DOWN,
	A_UP, A_DOWN,
	D_UP, D_DOWN,
	SPACE_UP, SPACE_DOWN,
	CONSOLE_TOGGLE,
	WINDOW_CLOSE
};

class InputManager
{
private:
	InputManager();
	static InputManager* pInstance;
	SDL_Event event;

public:
	static InputManager* getInstance();
	~InputManager();
	int checkInput();
};
#endif