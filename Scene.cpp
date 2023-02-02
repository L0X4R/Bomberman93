#include "Scene.h"

Scene::Scene()
{
	needReinit = true;
}

Scene::~Scene()
{
}

void Scene::init()
{
	needReinit = false;
}

void Scene::reinit()
{
	needReinit = true;
}
