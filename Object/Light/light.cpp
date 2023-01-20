#include "light.h"

Light::Light(Vec3 position){
    this->transform->position = position;
    this->color = Vec4(1.0f,1.0f,1.0f,1.0f);
}

void Light::step(){

}