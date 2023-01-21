#include "light.h"

Light::Light(Vec3 position) {
    this->transform->position = position;
}

Light::Light(Vec3 position, Vec4 color){
    this->transform->position = position;
    this->color = color;
}

Light::Light(Vec3 position, Vec4 color, float iAmb, float iDif, float iSpec, float kAmb, float kDif, float kSpec, float shininess) {
    this->transform->position = position;
    this->color = color;
    this->intensityAmbiental = std::max(0.0f, std::min(iAmb, 1.0f));
    this->intensityDiffuse = std::max(0.0f, std::min(iDif, 1.0f));
    this->intensitySpecular = std::max(0.0f, std::min(iSpec, 1.0f));
    this->reflectanceAmbiental = std::max(0.0f, std::min(kAmb, 1.0f));
    this->reflectanceDiffuse = std::max(0.0f, std::min(kDif, 1.0f));
    this->reflectanceSpecular = std::max(0.0f, std::min(kSpec, 1.0f));
    this->shininessCoef = std::max(shininess, 0.0f);
}