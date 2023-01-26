#pragma once
#pragma region INCLUDES
#include "ResourceManager.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "AudioManager.h"

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

struct position
{
	int x;
	int y;
};

struct _size
{
	int w;
	int h;
};

class gameObject
{
protected:
	position pos;
	_size size;

public:
	position getPosition()
	{
		return pos;
	}

	void setPosition(int _x, int _y)
	{
		pos.x = _x;
		pos.y = _y;
	}
};

