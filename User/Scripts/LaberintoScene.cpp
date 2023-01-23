#pragma once

#include "LaberintoScene.h"
#include "LookAtFollower.h"

Text* newTextTime;

void LaberintoScene::init() {
    genLaberinto();
    //camera->position = Vec3(0.0f, 0.0f, -18.0f);
    //camera->lookAt = Vec3(0.0f, 0.0f, -17.999f);

    camera->transform->position = Vec3(340.0f, 0.0f, 359.0f);
    camera->position = Vec3(340.0f, 0.0f, 359.0f);
    camera->lookAt = Vec3(340.0f, 0.0f, 358.999f);

    // Object* celda = new Object();
    // Mesh* celdaMesh = new Mesh(USER_PATH "Models\\celda3.trg", defaultVshader, defaultFshader, defaultTexture);
    // celda->addComponent(celdaMesh);
    // createObject(celda);

    //Object* newObject = new Object();
    //Mesh* newMesh = new Mesh(defaultuiModel, guiVshader, guiFshader, USER_PATH "Textures\\marcianitos.png");
    //UI* newInterface = new UI(camera);
    //newInterface->rectPosition = Vec2(0.5, 0.5);
    ////newInterface->layer = 1;
    //newObject->addComponent(newMesh);
    //newObject->addComponent(newInterface);
    //newObject->transform->scale = Vec3(2.0f, 2.0f, 1.0f);
    ////createObject(newObject);

    Input::restartTime();

    Object* textTime = new Object();
    newTextTime = new Text(to_string_with_precision(Input::getTime(), 2) + " s", defaultTextFontSize, Vec3(0.0f, 1.0f, 0));
    UI* newInterfaceTextTime = new UI(camera);
    newInterfaceTextTime->rectPosition = Vec2(0.82, 0.03);
    //newInterfaceText->layer = 2;
    textTime->addComponent(newTextTime);
    textTime->addComponent(newInterfaceTextTime);
    createObject(textTime);

    Light* newLight = new Light(Vec3(0, 3, 0));
    addLight(newLight);

    Light* newLight2 = new Light(Vec3(0, 3, 0), Vec4(1.0f,0.0f,0.0f,1.0f));
    //addLight(newLight2);

    BoxCollider* colliderCamera = new BoxCollider(camera);
    colliderCamera->bounds = Vec3(1, 1, 1);
    camera->addComponent(colliderCamera);

    //Object* debugBox = new Object();
    //Mesh* meshDebugBox = new Mesh(default3DModel,defaultVshader,defaultFshader,USER_PATH "Textures\\marcianitos.png");
    //LookAtFollower* lookAtDebugBox = new LookAtFollower(camera);
    //debugBox->transform->scale = Vec3(0.01f, 0.01f, 0.01f);
    ////debugBox->addComponent(meshDebugBox);
    //debugBox->addComponent(lookAtDebugBox);
    ////createObject(debugBox);
}


void LaberintoScene::createCelda(std::string modelo, int x, int z, int angulo, bool primera, bool segunda, bool tercera, bool cuarta){
    Object* celda = new Object();
    celda->transform->position.getX() = x;
    celda->transform->position.getZ() = z;
    celda->transform->rotation.getY() = Utils::radians(angulo);
    Mesh* meshCelda = new Mesh(modelo, defaultVshader, defaultFshader, USER_PATH "Textures\\lightRock.jpg");
    celda->addComponent(meshCelda);
    /*Collider* colliderCelda = new MeshCollider(celda);
    celda->addComponent(colliderCelda);*/
    BoxCollider* c;
    c = new BoxCollider(camera);
    celda->addComponent(c);
    c->offset = Vec3(9.5f,0,9.5f);
    c->bounds = Vec3(1,9*2,1);
    c = new BoxCollider(camera);
    celda->addComponent(c);
    c->offset = Vec3(-9.5f,0,9.5f);
    c->bounds = Vec3(1,9*2,1);
    c = new BoxCollider(camera);
    celda->addComponent(c);
    c->offset = Vec3(9.5f,0,-9.5f);
    c->bounds = Vec3(1,9*2,1);
    c = new BoxCollider(camera);
    celda->addComponent(c);
    c->offset = Vec3(-9.5f,0,-9.5f);
    c->bounds = Vec3(1,9*2,1);
    if (primera) {
        c = new BoxCollider(camera);
        celda->addComponent(c);
        c->offset = Vec3(0, 0, 9.5f);
        c->bounds = Vec3(9*2, 9*2, 1);
    }
    if (segunda) {
        c = new BoxCollider(camera);
        celda->addComponent(c);
        c->offset = Vec3(-9.5f, 0, 0);
        c->bounds = Vec3(1, 9*2, 9 * 2);
    }
    if (tercera) {
        c = new BoxCollider(camera);
        celda->addComponent(c);
        c->offset = Vec3(0, 0, -9.5f);
        c->bounds = Vec3(9*2, 9*2, 1);
    }
    if (cuarta) {
        c = new BoxCollider(camera);
        celda->addComponent(c);
        c->offset = Vec3(9.5f, 0, 0);
        c->bounds = Vec3(1, 9*2, 9 * 2);
    }
    createObject(celda);
    (*laberinto)[celda->getId()] = celda;
}

void LaberintoScene::genLaberinto() {
    std::ifstream archivo(USER_PATH "Models\\" NOMBRE_ARCHIVO);
    std::string linea;
    char delimitador = ';';
    int x, z = 0;
    char c;
    // Leemos la primer línea para descartarla si hay encabezado
    //getline(archivo, linea);
    // Leemos todas las líneas

    z = 0;
    while (std::getline(archivo, linea))
    {
        std::cout << linea << std::endl;
        //std::stringstream stream(linea); // Convertir la cadena a un stream
        //std::cout << stream.str() << std::endl;
        //std::string leyendaCelda;
        // Extraer todos los valores de esa fila
        x = 0;
        for (int i = 0; i < COLUMNSLAB; i++)
        {
            //std::getline(stream, leyendaCelda, delimitador);
            char c = linea[i];
            std::cout<<c<<std::endl;
            switch (c)
            {
            case 'O':
                createCelda(USER_PATH "Models\\celda0.trg",x,z,0,false,false,false,false);
                break;
            case 'A':
                createCelda(USER_PATH "Models\\celda3.trg",x,z,180,true, true,true, false);
                //createCelda(USER_PATH "Models\\celda3.trg",x,z,0,true,false,true,true);
                break;
            case 'B':
                createCelda(USER_PATH "Models\\celda3.trg",x,z,90, false,true, true,true);
                break;
            case 'C':
                createCelda(USER_PATH "Models\\celda3.trg",x,z,0, true, false, true, true);
                //createCelda(USER_PATH "Models\\celda3.trg",x,z,180,true,true,true,false);
                break;
            case 'D':
                createCelda(USER_PATH "Models\\celda3.trg",x,z,270, true,true, false,true);
                break;
            case 'E':
                createCelda(USER_PATH "Models\\celda2.trg",x,z,180,false,true,true,false);
                //createCelda(USER_PATH "Models\\celda2.trg",x,z,0,true,false,false,true);
                break;
            case 'F':
                createCelda(USER_PATH "Models\\celda2.trg",x,z,90,false,false,true,true);
                break;
            case 'G':
                createCelda(USER_PATH "Models\\celda2.trg",x,z,0,true,false,false,true);
                //createCelda(USER_PATH "Models\\celda2.trg",x,z,180,false,true,true,false);
                break;
            case 'H':
                createCelda(USER_PATH "Models\\celda2.trg",x,z,270,true,true,false,false);
                break;
            case 'I':
                createCelda(USER_PATH "Models\\celda2paralelo.trg",x,z,0,true,false,true,false);
                break;
            case 'J':
                createCelda(USER_PATH "Models\\celda2paralelo.trg",x,z,90,false,true,false,true);
                break;
            case 'K':
                createCelda(USER_PATH "Models\\probandoprobando.trg",x,z,180,false,true,false,false);
                //createCelda(USER_PATH "Models\\probandoprobando.trg",x,z,0,false,false,false,true);
                break;
            case 'L':
                createCelda(USER_PATH "Models\\probandoprobando.trg",x,z,90,false,false,true,false);
                break;
            case 'M':
                createCelda(USER_PATH "Models\\probandoprobando.trg",x,z,0,false,false,false,true);
                //createCelda(USER_PATH "Models\\probandoprobando.trg",x,z,180,false,true,false,false);
                break;
            case 'N':
                createCelda(USER_PATH "Models\\probandoprobando.trg",x,z,270,true,false,false,false);
                break;
            case 'P':
                createCelda(USER_PATH "Models\\celda4.trg", x, z,0,true,true,true,true);
                break;
            }
            x += CELLDISTANCE;
        }
        z += CELLDISTANCE;
    }

    archivo.close();
}

void LaberintoScene::userUpdate()
{
    newTextTime->changeText(to_string_with_precision(Input::getTime(), 2) + " s");
    Input::setCursorPos(windowWidth/2,windowHeight/2);
    Input::hideMouse();
}

LaberintoScene::~LaberintoScene(){
    delete laberinto;
}