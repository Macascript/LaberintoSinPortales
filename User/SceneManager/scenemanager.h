#pragma once

#include "../../Scene/scene.h"
#include "../../Engine/Commons/common.h"

class Scene;
class Camera;

class SceneManager {
private:
	static SceneManager* sceneManager;
	int actualSceneIndex = 2;
	Camera* camera;
public:
    SceneManager(Camera* cam);
	std::map<int, Scene*>* list;
	static void loadScene(int index);
	static Scene* actualScene();
	// void initSceneList();
};