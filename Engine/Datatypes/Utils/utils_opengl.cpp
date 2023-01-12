#pragma once
#include "utils.h"
#include "../Mat4/mat4_opengl.h"
#include "../Vec2/vec2_opengl.h"
#include "../Vec3/vec3_opengl.h"
#include "../Vec4/vec4_opengl.h"

#include "../../Commons/common_opengl.h"

Mat4 Utils::rotate(Mat4 &matrix, float a, Vec3 &vector) {
    return Mat4(glm::rotate(matrix.getMatrix(), a, vector.getVector()));
}

Mat4 Utils::translate(Mat4& matrix, Vec3& vector) {
    return Mat4(glm::translate(matrix.getMatrix(), vector.getVector()));
}

Mat4 Utils::scale(Mat4& matrix, Vec3& vector) {
    return Mat4(glm::scale(matrix.getMatrix(), vector.getVector()));
}

Mat4 Utils::lookAt(Vec3& position, Vec3& lookAt, Vec3& aux) {
    return Mat4(glm::lookAt(position.getVector(), lookAt.getVector(), aux.getVector()));
}

Mat4 Utils::ortho(float x, float y, float z, float k, float w, float a) {
    return Mat4(glm::ortho(x, y, z, k, w, a));
}

Mat4 Utils::ortho(float x, float y, float z, float k) {
    return Mat4(glm::ortho(x, y, z, k));
}

float Utils::radians(float degrees) {
    return glm::radians(degrees);
}

Mat4 Utils::perspective(float fovy, float aspect, float zNear, float zFar) {
    return Mat4(glm::perspective(fovy, aspect, zNear, zFar));
}
