#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#pragma region INCLUDES
#include <iostream>
#include "SDL.h"
#include "config.h"
using namespace std;
#pragma endregion

class InputManager
{
private:
	InputManager();
	static InputManager* pInstance;
	SDL_Event event;

	bool key_w;
	bool key_a;
	bool key_s;
	bool key_d;
	bool key_space;
	bool key_escape;
	bool key_comma;
	bool close_game;

public:
	static InputManager* getInstance();
	~InputManager();
	void update();
};
#endif