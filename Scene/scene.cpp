#pragma once
#include "scene.h"

Scene::Scene(Camera* cam) {
	camera = cam;
	objectList = new std::map<int, Object*>();
	addedObjectList = new std::map<int, Object*>();
	lightList = new std::vector<Light*>();
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

std::vector<Light*>* Scene::getLights() {
	return lightList;
}

void Scene::addLight(Light* light) {
	lightList->push_back(light);
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

std::vector<Object*>* Scene::getCollisions(Object* obj)
{
	std::vector<Object*>* objects = new std::vector<Object*>();

	int numFilas = sceneGrid->numFilas;
	int numColumnas = sceneGrid->numColumnas;

	int coordX = (obj->transform->position.x() - sceneGrid->minX) / (sceneGrid->tamX / numColumnas);
	int coordY = (obj->transform->position.y() - sceneGrid->minY) / (sceneGrid->tamY / numFilas);

	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{

			if ((((coordX + j) >= 0) && (coordX + j) < numColumnas) &&
				(((coordY + i) >= 0) && (coordY + i) < numFilas))
			{

				for (auto it = sceneGrid->grid[i + coordY][j + coordX].begin();
					it != sceneGrid->grid[i + coordY][j + coordX].end();
					it++)
				{
					if (it->second->collider->collision(obj->getComponent("collider"))) {
						objects->push_back(it->second);
					}
				}
			}
		}
	return objects;

}