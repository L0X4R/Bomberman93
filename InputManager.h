#pragma once
enum class InputKey
{
	ESCAPE,
	W,
	A,
	S,
	D,
	ESPACIO,
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

