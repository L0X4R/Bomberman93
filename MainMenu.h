#pragma once
#include "ResourceManager.h"
#include "VideoManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TextManager.h"

class MainMenu : public Scene
{
private:
	ResourceManager* rm;
	VideoManager* vm;
	AudioManager* am;
	TextManager* tm;
	InputManager* im;
	SceneManager* sm;

	// GRAPHICS
	const char* graphicPath = "assets/menu_background.png";
	int graphicID;

	rect BackgroundSize, InScreenPosition;

	rect mouse;

	rect playButton, playText;

	rect exitButton, exitText;

	rect scoreButton, scoreText;

public:
	void initLevel();

	void update();

	void render();

	bool isClickingButton(rect mouse, rect button);

	void setButtons();
};

