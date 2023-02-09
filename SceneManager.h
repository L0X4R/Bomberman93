#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#pragma region INCLUDES
#include <iostream>
#include <vector>
#include "Scene.h"
#include "VideoManager.h"

#include "WORLD_1_1.h"
#include "config.h"
using namespace std;
#pragma endregion

enum SceneEnum
{
	MAIN_MENU, OPTIONS_MENU, SCORE_MENU,
	LEVEL_1_1, LEVEL_1_2, LEVEL_1_3, LEVEL_1_4, LEVEL_1_5, LEVEL_1_6, LEVEL_1_7, LEVEL_1_8,
	LEVEL_2_1, LEVEL_2_2, LEVEL_2_3, LEVEL_2_4, LEVEL_2_5, LEVEL_2_6, LEVEL_2_7, LEVEL_2_8,
	NOT_LOAD, _LASTSCENE
};

#define NUM_SCENES _LASTSCENE

class SceneManager
{
private:
	SceneManager();
	static SceneManager* pInstance;

	SceneEnum loadedScene;

	vector<Scene*> scenesVector;

public:
	static SceneManager* getInstance();
	~SceneManager();

	void init();

	Scene* getLoadedScene();
	void loadScene(SceneEnum SceneNum);
};
#endif