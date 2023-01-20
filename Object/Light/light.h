#pragma once
#include "../../Engine/Commons/common.h"
#include "../object.h"

class Light: public Object{
public:
    float intensityAmbiental = 0.5f; //0-1
    float intensityDiffuse = 0.5f;  //0-1
    float intensitySpecular = 0.1f;  //0-1
    float reflectanceAmbiental = 0.35f;  //0-1
    float reflectanceDiffuse = 0.5f;  //0-1
    float reflectanceSpecular = 0.1f;  //0-1
    float shininessCoef = 32.0f;  //0-infinity
    Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

    Light(Vec3 position);
    Light(Vec3 position, Vec4 color);
    Light(Vec3 position, Vec4 color, float iAmb, float iDif, float iSpec, float kAmb, float kDif, float kSpec, float shineniness);

    virtual void step();
};