#include "GameOver.h"
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

void GameOver::initLevel()
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	am = AudioManager::getInstance();
	tm = TextManager::getInstance();
	im = InputManager::getInstance();
	sm = SceneManager::getInstance();
	HUD = hud::getInstance();

	graphicID = rm->loadAndGetGraphicID(graphicPath);

	BackgroundSize.x = 0;
	BackgroundSize.y = 0;
	BackgroundSize.w = SCREEN_WIDTH;
	BackgroundSize.h = SCREEN_HEIGHT;

	InScreenPosition.x = 0;
	InScreenPosition.y = 0;
	InScreenPosition.w = BackgroundSize.w;
	InScreenPosition.h = BackgroundSize.h;

	setButtons();

	mouse.w = 1;
	mouse.h = 1;
}

void GameOver::update()
{
	mouse.x = im->getMouseX();
	mouse.y = im->getMouseY();

	if (isClickingButton(mouse, returnButton))
	{
		sm->loadScene(SceneEnum::MAIN_MENU);
	}
}

void GameOver::render()
{
	vm->renderGraphic(graphicID, BackgroundSize, InScreenPosition);

	tm->DrawText("Return", returnText, 255, 255, 255, 255);

	stringstream formatedScore;

	formatedScore << setw(10) << setfill('0') << to_string(HUD->getScore());

	tm->DrawText(formatedScore.str(), scoreRect, 255, 255, 255, 255);
}

bool GameOver::isClickingButton(rect mouse, rect button)
{
	bool OverlapingX = false, OverlapingY = false;

	bool clicking = false;

	if (mouse.x + mouse.w > button.x && button.x + button.w > mouse.x) {
		OverlapingX = true;
	}

	if (mouse.y + mouse.h > button.y && button.y + button.h > mouse.y) {
		OverlapingY = true;
	}

	if (OverlapingX && OverlapingY && im->isClicking())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameOver::setButtons()
{
	scoreRect.x = 417;
	scoreRect.y = 447;
	scoreRect.w = 446;
	scoreRect.h = 66;

	returnButton.x = 482;
	returnButton.y = 684;
	returnButton.w = 317;
	returnButton.h = 65;

	returnText.x = 489;
	returnText.y = 690;
	returnText.w = 303;
	returnText.h = 48;
}