#pragma once

#include "../../Scene/scene.h"
#include "../../Engine/Commons/common.h"

class SceneManager {
public:
    SceneManager(Camera* cam);
	std::map<int, Scene*>* list;

	// void initSceneList();
};