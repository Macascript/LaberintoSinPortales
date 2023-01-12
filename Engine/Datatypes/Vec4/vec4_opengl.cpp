#pragma once
#include "vec4_opengl.h"

#include "../../Commons/common_opengl.h"

Vec4::Vec4() {
	vector = glm::vec4(0, 0, 0, 1.0f);
}

Vec4::Vec4(float x, float y, float z, float w){
	vector = glm::vec4(x,y,z,w);
}
Vec4::Vec4(glm::vec3 vector3, float w){
	vector = glm::vec4(vector3,w);
}
Vec4::Vec4(Vec3 vec3, float w){
	vector = glm::vec4(vec3.getVector(),w);
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