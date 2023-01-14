#pragma once

#include "../../Scene/scene.h"
#include "../../Engine/Commons/common.h"

class Scene;

class SceneManager {
private:
	static SceneManager* sceneManager;
	int actualSceneIndex = 0;
	Camera* camera;
public:
    SceneManager(Camera* cam);
	std::map<int, Scene*>* list;
	static void loadScene(int index);
	static Scene* actualScene();
	// void initSceneList();
};