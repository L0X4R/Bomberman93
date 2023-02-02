#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

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

enum SceneEnum
{
	MAIN_MENU, OPTIONS_MENU, SCORE_MENU,
	LEVEL_1_1, LEVEL_1_2, LEVEL_1_3, LEVEL_1_4, LEVEL_1_5, LEVEL_1_6, LEVEL_1_7, LEVEL_1_8,
	LEVEL_2_1, LEVEL_2_2, LEVEL_2_3, LEVEL_2_4, LEVEL_2_5, LEVEL_2_6, LEVEL_2_7, LEVEL_2_8,
	_LASTSCENE
};

#define NUM_SCENES _LASTSCENE

class SceneManager
{
private:
	SceneManager();
	static SceneManager* pInstance;

	SceneEnum loadedScene;

public:
	static SceneManager* getInstance();
	~SceneManager();

	void init();

	SceneEnum getLoadedScene();
	void loadScene(SceneEnum SceneNum);
};
#endif