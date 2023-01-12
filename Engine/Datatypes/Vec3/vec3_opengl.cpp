#pragma once
#include "vec3_opengl.h"

#include "../../Commons/common_opengl.h"

Vec3::Vec3() {
	vector = glm::vec3(0, 0, 0);
}

Vec3::Vec3(float x, float y, float z){
	vector = glm::vec3(x,y,z);
}

Vec3::Vec3(glm::vec2 vector2, float z){
	vector = glm::vec3(vector2,z);
}
Vec3::Vec3(Vec2 vec2, float z){
	vector = glm::vec3(vec2.getVector(),z);
}

glm::vec3 Vec3::getVector() {
	return vector;
}

float Vec3::x(){return vector.x;}
float Vec3::y(){return vector.y;}
float Vec3::z(){return vector.z;}

float& Vec3::getX(){return vector.x;}
float& Vec3::getY(){return vector.y;}
float& Vec3::getZ(){return vector.z;}