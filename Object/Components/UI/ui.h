#pragma once

#include "../../../Scene/scene.h"
//#include "../../../Engine/Datatypes/Utils/utils.h"
//#include "../Camera/camera.h"
//#include "../../component.h"

class Camera;

class UI: public Component{
protected:
    void destroy();
public:
    UI(Camera* camera);
    Camera* camera;
    Vec2 rectPosition = Vec2(0.5f,0.5f);
    void update();
    int layer = 1;
};