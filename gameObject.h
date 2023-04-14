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
#include "config.h"

using namespace std;
#pragma endregion

struct point
{
	int x;
	int y;
};

class gameObject
{
protected:
	gameObject();
	~gameObject();
	rect thisRect;
	rect worldRect;

	int bot_y = 0;

public:
	rect getRect()
	{
		return worldRect;
	}

	void setPosition(int _x, int _y)
	{
		worldRect.x = _x;
		worldRect.y = _y;
	}

	void setSize(int _w, int _h)
	{
		thisRect.w = _w;
		thisRect.h = _h;
	}

	void setBotY(int y)
	{
		bot_y = y;
	}

	int getBotY()
	{
		return bot_y;
	}

	bool CheckCollision(rect object1, point object2)
	{
		bool xOverlaps = false;
		bool yOverlaps = false;

		if ((object1.x < object2.x) && ((object1.x + object1.w) > object2.x))
		{
			xOverlaps = true;
		}

		if ((object1.y < object2.y) && ((object1.y + object1.h) > object2.y))
		{
			yOverlaps = true;
		}

		if (xOverlaps && yOverlaps)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

