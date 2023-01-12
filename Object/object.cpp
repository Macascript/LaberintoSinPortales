#pragma once
#include "object.h"

int Object::idCounter = 0;

Object::Object()
{
	this->id = idCounter;
	idCounter++;
	/*this->mesh->setColor(0, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	this->mesh->setColor(1, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	this->mesh->setColor(2, Vec4(0.0f, 0.0f, 1.0f, 1.0f));*/

	this->transform = new Transform();
}

Object::Object(std::string fileName)
{
	this->id = idCounter;
	idCounter++;
	//this->mesh = new Mesh(fileName);
	//this->shader = mesh->shader;

	/*this->transform->position = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->transform->modelMatrix = Mat4(1.0f);*/
	//this->collider = new Collider(this);
}

int Object::getId() {
	return this->id;
}

Component* Object::getComponent(std::string type){
	if (components->count(type) == 0){ // Precondition
		return nullptr;
	}
	return (*components)[type];
}

void Object::addComponent(Component* component){
	if (components->count(component->getType())){ // Precondition
		std::cout<<"ERROR: The object "<<id<<" already has a component of type "<<component->getType()<<std::endl;
		return;
		//throw std::exception("ERROR: The object "+id+" already has a component of type "+component->getType())
	}
	std::cout << "object.cpp addComponent():" << component->getType() << std::endl;
	component->setGameObject(this);
	(*components)[component->getType()] = component;
}

void Object::removeComponent(std::string type){
	if (components->count(type) == 0){ // Precondition
		std::cout << "ERROR: the object " << id << " doesn't have a component of type " << type << std::endl;
		return;
		//throw std::exception("ERROR: the object "+id+" doesn't have a component of type "+type);
	}

	delete (*components)[type];
	components->erase(type);
}

void Object::update(){
	for (auto it = components->begin(); it != components->end(); ++it){
    	it->second->update();
	}
}

Object::~Object(){
	for (auto it = components->begin(); it != components->end(); ++it){
    	delete it->second;
	}
	delete transform;
}