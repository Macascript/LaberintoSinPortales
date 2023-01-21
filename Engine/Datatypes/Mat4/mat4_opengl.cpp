#pragma once
#include "mat4_opengl.h"

Mat4::Mat4() {
	matrix = glm::mat4(1.0f);
}

Mat4::Mat4(float x) {
	matrix = glm::mat4(x);
}

Mat4::Mat4(glm::mat4 matrix) {
	this->matrix = matrix;
}

glm::mat4 Mat4::getMatrix() {
	return matrix;
}

Vec4 Mat4::operator * (Vec4 vec) {
	return Vec4(matrix * vec.getVector());
}

Mat4 Mat4::operator * (Mat4 mat) {
	return Mat4(matrix * mat.getMatrix());
}