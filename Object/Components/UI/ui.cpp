#include "ui.h"

#define PI 3.1415692f

UI::UI(Camera* camera){
    type = "ui";
    this->camera = camera;  
}

//camara position: 0,0,1
//camera lookAt: 0,0,-3
//object position 0,0,0

void UI::update(){
    // fieldOfViewX = 2 * atan(tan(fieldOfViewY * 0.5) * aspect)
    //float fovy = camera->fovy; //pi/2
    //float d = camera->zNear + (0.01f * layer); //0.01
    //float aspect = camera->aspect;
    //float fovx = 2.0f * atan(tan(fovy * 0.25f) * aspect);
    //float h = (fovy/2.0f) / cos((fovy/4.0f));
    //float w = (fovx/2.0f) / cos((fovx/4.0f));
    Vec3 newPos;

    if (!gameObject->getComponent("mesh")) 
    {
        newPos = Vec3(
            /*camera->position.x() - w / 2.0f + (rectPosition.x() * windowWidth),
            camera->position.y() - h / 2.0f + (rectPosition.y() * windowHeight),*/
            rectPosition.x() * windowWidth,
            rectPosition.y() * windowHeight,
            camera->lookAt.z() - layer
        );
    }
    else 
    {
        newPos = Vec3(
            /*camera->position.x() - w / 2.0f + (((rectPosition.x() * 1.67f) - 0.795f) / 100 * windowWidth),
            camera->position.y() - h / 2.0f + (((rectPosition.y() * 1.67f) - 0.75f) / 100 * windowHeight),*/
            (rectPosition.x() * 10.688f) - 5.34855f,
            (rectPosition.y() * 8.01599) - 4.02505f,
            camera->lookAt.z() - layer
        );
    }
    //if (gameObject->getComponent("collider")) std::cout<<"UI position: ("<<newPos.x()<<","<<newPos.y()<<","<< gameObject->transform->position.z()<<")"<<std::endl;
    gameObject->transform->position = newPos;
}

void UI::destroy(){

}