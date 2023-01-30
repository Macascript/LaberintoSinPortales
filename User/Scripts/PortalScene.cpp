#include "PortalScene.h"

void PortalScene::init(){
    Object* referencia = new Object();
    referencia->transform->position = Vec3(0.0f, 0.0f, -15.0f);
    Mesh* meshCelda = new Mesh(USER_PATH "Models\\celda1.trg", defaultVshader, defaultFshader, USER_PATH "Textures\\messyRocks_floor.jpg");
    referencia->addComponent(meshCelda);
    createObject(referencia);

    Object* referencia2 = new Object();
    referencia2->transform->position = Vec3(0.0f, 0.0f, 5.0f);
    Mesh* meshCelda2 = new Mesh(USER_PATH "Models\\celda1.trg", defaultVshader, defaultFshader, USER_PATH "Textures\\messyRocks_floor.jpg");
    referencia2->addComponent(meshCelda2);
    createObject(referencia2);

    Object* referencia3 = new Object();
    referencia3->transform->position = Vec3(0.0f, 0.0f, 25.0f);
    Mesh* meshCelda3 = new Mesh(USER_PATH "Models\\celda1.trg", defaultVshader, defaultFshader, USER_PATH "Textures\\messyRocks_floor.jpg");
    referencia3->addComponent(meshCelda3);
    createObject(referencia3);

    Object* portal = new Object();
    Mesh* portalMesh = new Mesh(default3DModel, defaultVshader, defaultRenderTextureFshader, "");
    portal->addComponent(portalMesh);
    RenderToTexture* renderToTexture = new RenderToTexture(portal,20,10);
    portal->addComponent(renderToTexture);
    createObject(portal);

    Light* newLight = new Light(Vec3(0.0f, 0.0f, -15.0f));
    addLight(newLight);
}

void PortalScene::userUpdate(){
    Input::setCursorPos(windowWidth / 2, windowHeight / 2);
    Input::hideMouse();
}