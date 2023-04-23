#include "SceneManager.h"
#include "VideoManager.h"
#include "MainMenu.h"

SceneManager* SceneManager::pInstance = NULL;

SceneManager::SceneManager()
{
	LOG("CREANDO EL GESTOR DE ESCENAS.");
	loadedScene = NOT_LOAD;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new SceneManager();
	}

	return pInstance;
}

void SceneManager::init()
{
	scenesVector.resize(NUM_SCENES);

	VideoManager* WINDOW = VideoManager::getInstance();

	MainMenu* mMenu = new MainMenu();
	WORLD_2_1* w2_1 = new WORLD_2_1();

	scenesVector[MAIN_MENU] = mMenu;
	scenesVector[LEVEL_2_1] = w2_1;
}

Scene* SceneManager::getLoadedScene()
{
	return scenesVector[loadedScene];
}

void SceneManager::loadScene(SceneEnum SceneNum)
{
	loadedScene = SceneNum;
	scenesVector[SceneNum]->init();
}
