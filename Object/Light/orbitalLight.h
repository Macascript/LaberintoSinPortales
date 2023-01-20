#pragma once
#include "common.h"
#include "light.h"

class OrbitalLight: public Light{
public:
    glm::vec3 orbitalCentre;
    float radio;
    float angle;
    glm::vec3 front = glm::vec3(0.0f,0.0f,0.0f);

    OrbitalLight(glm::vec3 position,glm::vec3 orbitalCentre, float radio, float startAngle): Light(position){
        this->orbitalCentre = orbitalCentre;
        front.z += radio;
        this->radio = radio;
        this->angle = startAngle;
    };
    virtual void step() override;
};