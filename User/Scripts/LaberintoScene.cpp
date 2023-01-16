#pragma once

#include "LaberintoScene.h"

void LaberintoScene::init() {
    genLaberinto();
    // Object* celda = new Object();
    // Mesh* celdaMesh = new Mesh(USER_PATH "Models\\celda3.trg", defaultVshader, defaultFshader, defaultTexture);
    // celda->addComponent(celdaMesh);
    // createObject(celda);

    Object* newObject = new Object();
    Mesh* newMesh = new Mesh(defaultuiModel, guiVshader, guiFshader, USER_PATH "Textures\\marcianitos.png");
    UI* newInterface = new UI(camera);
    newInterface->rectPosition = Vec2(0.5, 0.5);
    //newInterface->layer = 1;
    newObject->addComponent(newMesh);
    newObject->addComponent(newInterface);
    newObject->transform->scale = Vec3(2.0f, 2.0f, 1.0f);
    createObject(newObject);
}

void LaberintoScene::createCelda(std::string modelo, int x, int z, int angulo){
    Object* celda = new Object();
    celda->transform->position.getX() = x;
    celda->transform->position.getZ() = z;
    celda->transform->rotation.getY() = Utils::radians(angulo);
    Mesh* meshCelda = new Mesh(modelo, defaultVshader, defaultFshader, defaultTexture);
    celda->addComponent(meshCelda);
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
        std::stringstream stream(linea); // Convertir la cadena a un stream
        std::cout << stream.str() << std::endl;
        std::string leyendaCelda;
        // Extraer todos los valores de esa fila
        x = 0;
        for (int i = 0; i < COLUMNSLAB; i++)
        {
            std::getline(stream, leyendaCelda, delimitador);
            std::cout<<leyendaCelda<<std::endl;
            switch (std::stoi(leyendaCelda))
            {
            case 0:
                createCelda(USER_PATH "Models\\celda0.trg",x,z,0);
                break;
            case 1:
                createCelda(USER_PATH "Models\\celda3.trg",x,z,180);
                break;
            case 2:
                createCelda(USER_PATH "Models\\celda3.trg",x,z,90);
                break;
            case 3:
                createCelda(USER_PATH "Models\\celda3.trg",x,z,0);
                break;
            case 4:
                createCelda(USER_PATH "Models\\celda3.trg",x,z,270);
                break;
            case 5:
                createCelda(USER_PATH "Models\\celda2.trg",x,z,180);
                break;
            case 6:
                createCelda(USER_PATH "Models\\celda2.trg",x,z,90);
                break;
            case 7:
                createCelda(USER_PATH "Models\\celda2.trg",x,z,0);
                break;
            case 8:
                createCelda(USER_PATH "Models\\celda2.trg",x,z,270);
                break;
            case 9:
                createCelda(USER_PATH "Models\\celda2paralelo.trg",x,z,0);
                break;
            case 10:
                createCelda(USER_PATH "Models\\celda2paralelo.trg",x,z,90);
                break;
            case 11:
                createCelda(USER_PATH "Models\\celda1.trg",x,z,180);
                break;
            case 12:
                createCelda(USER_PATH "Models\\celda1.trg",x,z,90);
                break;
            case 13:
                createCelda(USER_PATH "Models\\celda1.trg",x,z,0);
                break;
            case 14:
                createCelda(USER_PATH "Models\\celda1.trg",x,z,270);
                break;
            case 15:
                createCelda(USER_PATH "Models\\celda4.trg", x, z,0);
                break;
            }
            x += CELLDISTANCE;
        }
        z += CELLDISTANCE;
    }

    archivo.close();
}

LaberintoScene::~LaberintoScene(){
    delete laberinto;
}