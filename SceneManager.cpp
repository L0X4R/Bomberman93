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

	WORLD_2_1* w2_1 = new WORLD_2_1();

	scenesVector[LEVEL_2_1] = w2_1;

	w2_1->init();
}

Scene* SceneManager::getLoadedScene()
{
	return scenesVector[loadedScene];
}

void SceneManager::loadScene(SceneEnum SceneNum)
{
	loadedScene = SceneNum;
}
