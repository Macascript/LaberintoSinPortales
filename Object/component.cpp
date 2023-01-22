#include "component.h"

void Component::setGameObject(Object* obj){
    gameObject = obj;
}

Object* Component::getGameObject() {
    return gameObject;
}

std::string Component::getType(){
    return type;
}

void Component::destroy(){}

void Component::update(){}

Component::~Component(){
    destroy();
}