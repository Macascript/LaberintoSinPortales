#pragma once

#include "scenemanager.h"
#include "../Scripts/MenuScene.h"
#include "../Scripts/LaberintoScene.h"

SceneManager* SceneManager::sceneManager = nullptr;

SceneManager::SceneManager(Camera* camera){
    this->camera = camera;
    sceneManager = this;
    this->list = new std::map<int,Scene*>();
    // USER TODO:
    (*this->list)[0] = new MenuScene(camera);
    (*this->list)[1] = new LaberintoScene(camera);
    //
}

void SceneManager::loadScene(int index) {
    sceneManager->actualSceneIndex = index;
    std::cout<<"Cargando la escena "<<index<<std::endl;
    actualScene()->init();
    actualScene()->setCamera(sceneManager->camera);
}

Scene* SceneManager::actualScene(){
    return (*sceneManager->list)[sceneManager->actualSceneIndex];
}