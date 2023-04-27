#pragma once
#include "ResourceManager.h"
#include "VideoManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TextManager.h"
#include "hud.h"

class GameOver : public Scene
{
	ResourceManager* rm;
	VideoManager* vm;
	AudioManager* am;
	TextManager* tm;
	InputManager* im;
	SceneManager* sm;
	hud* HUD;

	// GRAPHICS
	const char* graphicPath = "assets/gameover.png";
	int graphicID;

	rect BackgroundSize, InScreenPosition;

	rect mouse;

	rect returnButton, returnText;

	rect scoreRect;

public:
	void initLevel();

	void update();

	void render();

	bool isClickingButton(rect mouse, rect button);

	void setButtons();
};

