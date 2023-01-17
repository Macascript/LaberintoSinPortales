#pragma once

#include "MenuScene.h"
void loadLaberinto();
void loadOpciones();
void MenuScene::init() {

    /*Object* background = new Object();
    Mesh* backgroundMesh = new Mesh();
    UI* userInterface = new UI(camera);
    userInterface->rectPosition = Vec2(0,0);
    background->addComponent(backgroundMesh);
    background->addComponent(userInterface);
    createObject(background);*/

    Object* title = new Object();
    Text* newTitleText = new Text("LABERINTO PORTALES", defaultTextFontSize, Vec3(0.0f, 1.0f, 0));
    UI* newInterfaceTitle = new UI(camera);
    newInterfaceTitle->rectPosition = Vec2(0.21, 0.8);
    //newInterfaceText2->layer = 0;
    title->addComponent(newTitleText);
    title->addComponent(newInterfaceTitle);
    createObject(title);

    Object* button1 = new Object();
    Mesh* newMeshButton1 = new Mesh(defaultuiModel, guiVshader, guiFshader, USER_PATH "Textures\\boton.png");
    UI* newInterfaceButton1 = new UI(camera);
    newInterfaceButton1->rectPosition = Vec2(0.29,0.48);
    //newInterfaceButton1->rectPosition = Vec2(2.87, 2.87);
    //newInterfaceButton1->rectPosition = Vec2(0, 0);
    //newInterface->layer = 1;
    button1->addComponent(newMeshButton1);
    button1->addComponent(newInterfaceButton1);
    button1->transform->scale = Vec3(4.0f, 2.0f, 1.0f);
    Collider* colliderButton1 = new Collider(button1);
    button1->addComponent(colliderButton1);
    Button* componentButton1 = new Button(button1, &loadLaberinto);
    button1->addComponent(componentButton1);
    createObject(button1);
  
    Object* textButton1 = new Object();
    Text* newTextButton1 = new Text("INICIAR", defaultTextFontSize, Vec3(0.0f, 1.0f, 0));
    UI* newInterfaceTextButton1 = new UI(camera);
    newInterfaceTextButton1->rectPosition = Vec2(0.39,0.59);
    //newInterfaceText->layer = 2;
    textButton1->addComponent(newTextButton1);
    textButton1->addComponent(newInterfaceTextButton1);
    createObject(textButton1);

    Object* button2 = new Object();
    Mesh* newMeshButton2 = new Mesh(defaultuiModel, guiVshader, guiFshader, USER_PATH "Textures\\boton.png");
    UI* newInterfaceButton2 = new UI(camera);
    newInterfaceButton2->rectPosition = Vec2(0.29, 0.21);
    //newInterface->layer = 1;
    button2->addComponent(newMeshButton2);
    button2->addComponent(newInterfaceButton2);
    button2->transform->scale = Vec3(4.0f, 2.0f, 1.0f);
    Collider* colliderButton2 = new Collider(button2);
    button2->addComponent(colliderButton2);
    Button* componentButton2 = new Button(button2, &loadOpciones);
    button2->addComponent(componentButton2);
    createObject(button2);

    Object* textButton2 = new Object();
    Text* newTextButton2 = new Text("OPCIONES", defaultTextFontSize, Vec3(0.0f, 1.0f, 0));
    UI* newInterfaceTextButton2 = new UI(camera);
    newInterfaceTextButton2->rectPosition = Vec2(0.35, 0.32);
    //newInterfaceText->layer = 2;
    textButton2->addComponent(newTextButton2);
    textButton2->addComponent(newInterfaceTextButton2);
    createObject(textButton2);
}

void loadLaberinto(){
    SceneManager::loadScene(1);
}

void loadOpciones() {
    SceneManager::loadScene(1);
}

void MenuScene::userUpdate() {

}