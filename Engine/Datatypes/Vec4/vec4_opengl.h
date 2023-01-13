#pragma once
#include "../Vec3/vec3_opengl.h"
#include "../../Commons/common_opengl.h"

class Vec4 {
private:
    glm::vec4 vector = glm::vec4(0,0,0,1.0f);
public:
    Vec4();
    Vec4(float x, float y, float z, float w);
    Vec4(glm::vec2 vector2, float z, float w);
    Vec4(Vec2 vec2,float z, float w);
    Vec4(glm::vec3 vector3, float w);
    Vec4(Vec3 vec3, float w);
    Vec4(glm::vec4 vector4);
    glm::vec4 getVector();
    float x();
    float y();
    float z();
    float w();
    float& getX();
    float& getY();
    float& getZ();
    float& getW();

    Vec4 operator + (Vec4 vec4);
};
