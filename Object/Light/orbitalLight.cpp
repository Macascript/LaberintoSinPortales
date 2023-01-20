#include "orbitalLight.h"

void OrbitalLight::step(){
    angle += 0.01f;
    transform->position.getX() = cos(angle) * front.x() + sin(angle) * front.z() + orbitalCentre.x();
    transform->position.getZ() = -sin(angle) * front.x() + cos(angle) * front.z() + orbitalCentre.z();
}