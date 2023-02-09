#include "SceneManager.h"

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

	WORLD_1_1* w1_1 = new WORLD_1_1();

	scenesVector[LEVEL_1_1] = w1_1;

	w1_1->init();
}

Scene* SceneManager::getLoadedScene()
{
	return scenesVector[loadedScene];
}

void SceneManager::loadScene(SceneEnum SceneNum)
{
	loadedScene = SceneNum;
}
