#include "orbitalLight.h"

void OrbitalLight::update(){
    Light::update();
    angle += 0.01f;
    transform->position.getX() = cos(angle) * front.x() + sin(angle) * front.z() + orbitalCentre.x();
    transform->position.getZ() = -sin(angle) * front.x() + cos(angle) * front.z() + orbitalCentre.z();
}