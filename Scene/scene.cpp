#pragma once
#include "scene.h"

Scene::Scene(Camera* cam) {
	camera = cam;
	objectList = new std::map<int, Object*>();
	addedObjectList = new std::map<int, Object*>();
	//std::cout << "patata" << std::endl;
}

Camera* Scene::getCamera(){
	return camera;
}

void Scene::setCamera(Camera* camera) {
	this->camera = camera;
}

void Scene::createObject(Object* object){
	// (*objectList)[object->getId()] = object;
	addObject(object);
}

void Scene::addObject(Object* object) {
	(*addedObjectList)[object->getId()] = object;
	//object->transform->computeMatrix();
}

void Scene::removeObject(Object* object) {
	auto it = objectList->find(object->getId());
	it->second->markedDelete = true;
}

void Scene::update(){
	for(auto it=addedObjectList->begin();
            it!=addedObjectList->end();
            it++)
    {

        (*objectList)[it->first]=it->second;
    }
    addedObjectList->clear();


    /*for(auto it=objectList->begin();
		it!= objectList->end();
		it++)
	{
		it->second->updateCollider();	
	}*/
	
	// sceneGrid->update();
	camera->step();
	for(auto it=objectList->begin();
		it!= objectList->end();
		it++)
	{
		it->second->update();	
	}

	for(auto it= objectList->begin();
		it!= objectList->end();
		)
	{
		if(it->second->markedDelete)
		{	delete it->second;
			it= objectList->erase(it);
		}else{
			it++;
		}
	}

	// for(int i = 0; i < lightList->size(); i++){
	// 	(*lightList)[i]->step();
	// }
	SceneManager::actualScene()->userUpdate();
}