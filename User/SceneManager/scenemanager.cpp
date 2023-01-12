#pragma once

#include "scenemanager.h"
#include "../Scripts/MenuScene.h"

SceneManager::SceneManager(Camera* camera){
    this->list = new std::map<int,Scene*>();
    // USER TODO:
    (*this->list)[0] = new MenuScene(camera);

    //
}