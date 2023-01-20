#pragma once
#include "light.h"

class OrbitalLight: public Light{
public:
    Vec3 orbitalCentre;
    float radio;
    float angle;
    Vec3 front = Vec3(0.0f,0.0f,0.0f);

    OrbitalLight(Vec3 position, Vec3 orbitalCentre, float radio, float startAngle): Light(transform->position){
        this->orbitalCentre = orbitalCentre;
        front.getZ() += radio;
        this->radio = radio;
        this->angle = startAngle;
    };
    virtual void step() override;
};