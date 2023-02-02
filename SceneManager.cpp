#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "config.h"
using namespace std;
#pragma endregion

SceneManager* SceneManager::pInstance = NULL;

SceneManager::SceneManager()
{
	LOG("CREANDO EL GESTOR DE ESCENAS.");
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
}

SceneEnum SceneManager::getLoadedScene()
{
	return loadedScene;
}

void SceneManager::loadScene(SceneEnum SceneNum)
{
	loadedScene = SceneNum;
}
