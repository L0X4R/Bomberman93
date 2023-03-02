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

struct objRect
{
	int x;
	int y;
	int w;
	int h;
};

class gameObject
{
protected:
	gameObject();
	~gameObject();
	objRect objectRect;

public:
	objRect getRect()
	{
		return objectRect;
	}

	void setPosition(int _x, int _y)
	{
		objectRect.x = _x;
		objectRect.y = _y;
	}

	void setSize(int _w, int _h)
	{
		objectRect.w = _w;
		objectRect.h = _h;
	}

	bool CheckCollision(objRect object1, objRect object2)
	{
		bool xOverlaps = false;
		bool yOverlaps = false;

		if (object1.x < (object2.x + object2.w) && (object1.x + object1.w) > object2.x)
		{
			xOverlaps = true;
		}

		if (object1.y < (object2.y + object2.h) && (object1.y + object1.h) > object2.y)
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

