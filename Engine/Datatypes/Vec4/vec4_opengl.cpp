#pragma once
#include "vec4_opengl.h"

#include "../../Commons/common_opengl.h"

Vec4::Vec4() {
	vector = glm::vec4(0, 0, 0, 1.0f);
}

Vec4::Vec4(float x, float y, float z, float w){
	vector = glm::vec4(x,y,z,w);
}

Vec4::Vec4(glm::vec2 vector2, float z, float w){
	vector = glm::vec4(vector2,z,w);
}

Vec4::Vec4(glm::vec3 vector3, float w){
	vector = glm::vec4(vector3,w);
}

Vec4::Vec4(Vec2 vec2,float z, float w){
	vector = glm::vec4(vec2.getVector(),z,w);
}

Vec4::Vec4(Vec3 vec3, float w){
	vector = glm::vec4(vec3.getVector(),w);
}
Vec4::Vec4(glm::vec4 vector4) {
	vector = vector4;
}

glm::vec4 Vec4::getVector() {
	return vector;
}

float Vec4::x(){return vector.x;}
float Vec4::y(){return vector.y;}
float Vec4::z(){return vector.z;}
float Vec4::w(){return vector.w;}

float& Vec4::getX(){return vector.x;}
float& Vec4::getY(){return vector.y;}
float& Vec4::getZ(){return vector.z;}
float& Vec4::getW(){return vector.w;}

Vec4 Vec4::operator + (Vec4 vec4){
	return Vec4(vector + vec4.getVector());
}
