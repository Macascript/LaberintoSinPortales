#pragma once

#include "MenuScene.h"

void MenuScene::init() {

    Object* background = new Object();
    Mesh* backgroundMesh = new Mesh();
    UI* userInterface = new UI(camera);
    userInterface->rectPosition = Vec2(0,0);
    //userInterface->layer = 20;
    background->addComponent(backgroundMesh);
    background->addComponent(userInterface);

    Object* newTextObject2 = new Object();
    Text* newText2 = new Text("PATATAS", defaultTextFontSize, Vec3(0.0f, 1.0f, 0));
    UI* newInterfaceText2 = new UI(camera);
    newInterfaceText2->rectPosition = Vec2(0, 0);
    //newInterfaceText2->layer = 0;
    newTextObject2->addComponent(newText2);
    newTextObject2->addComponent(newInterfaceText2);

    Object* newObject = new Object();
    Mesh* newMesh = new Mesh(defaultuiModel, guiVshader, guiFshader, USER_PATH "Textures\\marcianitos.png");
    UI* newInterface = new UI(camera);
    newInterface->rectPosition = Vec2(0.1,0.7);
    //newInterface->layer = 1;
    newObject->addComponent(newMesh);
    newObject->addComponent(newInterface);
    newObject->transform->scale = Vec3(2.0f, 2.0f, 1.0f);
  
    Object* newTextObject = new Object();
    Text* newText = new Text("EXTRACTO", defaultTextFontSize, Vec3(0.0f, 1.0f, 0));
    UI* newInterfaceText = new UI(camera);
    newInterfaceText->rectPosition = Vec2(0.5,0.5);
    //newInterfaceText->layer = 2;
    newTextObject->addComponent(newText);
    newTextObject->addComponent(newInterfaceText);


    //Object* newButton = new Object();
    Collider* colliderButton = new Collider(newObject);
    newObject->addComponent(colliderButton);
    Button* componentButton = new Button(newObject);
    newObject->addComponent(componentButton);


    createObject(newObject);
    //createObject(background);
    
    createObject(newTextObject2);
    createObject(newTextObject);

    //createObject(newButton);
}