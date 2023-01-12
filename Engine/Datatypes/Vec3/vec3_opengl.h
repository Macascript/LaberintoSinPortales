#pragma once
#include "../../Commons/common_opengl.h"
#include "../Vec2/vec2_opengl.h"

class Vec3 {
private:
    glm::vec3 vector = glm::vec3(0,0,0);
public:
    Vec3();
    Vec3(float x, float y, float z);
    Vec3(glm::vec2 vector2,float z);
    Vec3(Vec2 vec2,float z);
    glm::vec3 getVector();
    float x();
    float y();
    float z();
    float& getX();
    float& getY();
    float& getZ();
};