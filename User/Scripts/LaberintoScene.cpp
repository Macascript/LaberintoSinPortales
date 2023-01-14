#pragma once

#include "LaberintoScene.h"

void LaberintoScene::init() {
    genLaberinto();
    // Object* celda = new Object();
    // Mesh* celdaMesh = new Mesh(USER_PATH "Models\\celda3.trg", defaultVshader, defaultFshader, defaultTexture);
    // celda->addComponent(celdaMesh);
    // createObject(celda);
}

void LaberintoScene::createCelda(std::string modelo,int angulo){
    Object* celda = new Object();
    celda->transform->rotation.getY() = angulo;
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
                createCelda(USER_PATH "Models\\celda0.trg",0);
                break;
            case 1:
                createCelda(USER_PATH "Models\\celda3.trg",0);
                break;
            case 2:
                createCelda(USER_PATH "Models\\celda3.trg",90);
                break;
            case 3:
                createCelda(USER_PATH "Models\\celda3.trg",180);
                break;
            case 4:
                createCelda(USER_PATH "Models\\celda3.trg",270);
                break;
            case 5:
                createCelda(USER_PATH "Models\\celda2.trg",0);
                break;
            case 6:
                createCelda(USER_PATH "Models\\celda2.trg",90);
                break;
            case 7:
                createCelda(USER_PATH "Models\\celda2.trg",180);
                break;
            case 8:
                createCelda(USER_PATH "Models\\celda2.trg",270);
                break;
            case 9:
                createCelda(USER_PATH "Models\\celda2paralelo.trg",0);
                break;
            case 10:
                createCelda(USER_PATH "Models\\celda2paralelo.trg",90);
                break;
            case 11:
                createCelda(USER_PATH "Models\\celda1.trg",0);
                break;
            case 12:
                createCelda(USER_PATH "Models\\celda1.trg",90);
                break;
            case 13:
                createCelda(USER_PATH "Models\\celda1.trg",180);
                break;
            case 14:
                createCelda(USER_PATH "Models\\celda1.trg",270);
                break;
            case 15:
                createCelda(USER_PATH "Models\\celda4.trg",0);
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