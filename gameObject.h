#pragma once

struct position
{
	int x;
	int y;
};

class gameObject
{
protected:
	position pos;

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

