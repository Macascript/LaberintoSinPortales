#pragma once
#include "mat4.h"
#include "../../Commons/common_opengl.h"
#include "../Vec4/vec4_opengl.h"

class Mat4 {
private:
    glm::mat4 matrix = glm::mat4(1.0f);
public:
    Mat4();
    Mat4(float x);
    Mat4(glm::mat4 matrix);
    glm::mat4 getMatrix();
    
    Vec4 operator * (Vec4 vec);
};