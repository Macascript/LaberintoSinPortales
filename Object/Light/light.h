#pragma once
#include "../../Engine/Commons/common.h"
#include "../object.h"

class Light: public Object{
public:
    float ambiental = 0.175f;
    float diffuse = 0.5f;
    float specular = 0.1f;
    int powSpecular = 256;
    Vec3 color;
};