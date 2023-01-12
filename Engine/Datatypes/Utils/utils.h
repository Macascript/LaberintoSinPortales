#pragma once
#define OpenGLsystem
#include "../Vec2/vec2.h"
#include "../Vec3/vec3.h"
#include "../Vec4/vec4.h"
#include "../Mat4/mat4.h"

class Utils{
public:
    static Mat4 translate(Mat4 &matrix,Vec3 &vector);
    static Mat4 rotate(Mat4 &matrix, float a, Vec3 &vector);
    static Mat4 scale(Mat4 &matrix, Vec3 &vector);
    static Mat4 lookAt(Vec3 &position, Vec3 &lookAt, Vec3 &aux); //en codigo antiguo aux = glm::vec3(0, 1.0f,0) siempre en camera
    static Mat4 ortho(float x, float y, float z, float k, float w, float a);
    static Mat4 ortho(float x, float y, float z, float k);
    static float radians(float degrees);
    static Mat4 perspective(float fovy, float aspect, float zNear, float zFar);
    static Mat4 value_ptr(Mat4 &matrix);
};