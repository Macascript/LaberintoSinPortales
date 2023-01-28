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

//Mat4 Utils::value_ptr(Mat4 &matrix) {
//    return Mat4(glm::value_ptr(matrix.getMatrix()));
//}

Vec3 Utils::cross(Vec3& vector1, Vec3& vector2) {
    return Vec3(glm::cross(vector1.getVector(), vector2.getVector()));
}

float Utils::dot(Vec3& vector1, Vec3& vector2) {
    return glm::dot(vector1.getVector(), vector2.getVector());
}

Vec3 Utils::normalize(Vec3& vector) {
    return Vec3(glm::normalize(vector.getVector()));
}
