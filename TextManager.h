#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#pragma region INCLUDES
#include <iostream>
#include <vector>
#include <string>
#include "SDL_TTF.h"
#include "VideoManager.h"

using namespace std;
#pragma endregion

class TextManager
{
	struct reward
	{
		SDL_Texture* txReward;
		SDL_Rect position;

		int defaultTime = 2000;
		int remaining = defaultTime;
		float alpha = 255;
	};

private:
	TextManager();
	static TextManager* pInstance;

	vector<reward*> scoreRewards;

	VideoManager* vm;

	TTF_Font* font;

public:
	static TextManager* getInstance();
	~TextManager();

	rect Camera;

	void setFont(int size, const char* fontPath);

	void DrawText(string text, rect textRect, int R, int G, int B, int A);

	void addReward(int points, rect textRect, int R, int G, int B, int A);

	void renderRewards();
};

#endif

