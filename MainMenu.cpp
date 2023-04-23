#include "MainMenu.h"

void MainMenu::initLevel()
{
	rm = ResourceManager::getInstance();
	vm = VideoManager::getInstance();
	am = AudioManager::getInstance();
	tm = TextManager::getInstance();
	im = InputManager::getInstance();
	sm = SceneManager::getInstance();

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

void MainMenu::update()
{
	mouse.x = im->getMouseX();
	mouse.y = im->getMouseY();

	if (isClickingButton(mouse, playButton))
	{
		sm->loadScene(SceneEnum::LEVEL_2_1);
	}

	if (isClickingButton(mouse, exitButton))
	{
		im->closeGame();
	}
}

void MainMenu::render()
{
	vm->renderGraphic(graphicID, BackgroundSize, InScreenPosition);

	tm->DrawText("Play Game", playText, 255, 255, 255, 255);
	tm->DrawText("Scoreboard", scoreText, 255, 255, 255, 255);
	tm->DrawText("Exit", exitText, 255, 255, 255, 255);
}

bool MainMenu::isClickingButton(rect mouse, rect button)
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

void MainMenu::setButtons()
{
	playButton.x = 50;
	playButton.y = 458;
	playButton.w = 317;
	playButton.h = 65;

	playText.x = 60;
	playText.y = 465;
	playText.w = 296;
	playText.h = 47;

	scoreText.x = 60;
	scoreText.y = 560;
	scoreText.w = 253;
	scoreText.h = 44;

	exitButton.x = 50;
	exitButton.y = 646;
	exitButton.w = 217;
	exitButton.h = 65;

	exitText.x = 80;
	exitText.y = 655;
	exitText.w = 160;
	exitText.h = 41;
}
