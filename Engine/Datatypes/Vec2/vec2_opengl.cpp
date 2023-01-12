#pragma once
#include "vec2_opengl.h"

Vec2::Vec2() {
	vector = glm::vec2(0,0);
}

Vec2::Vec2(float x, float y){
	vector = glm::vec2(x,y);
}

glm::vec2 Vec2::getVector() {
	return vector;
}

float Vec2::x(){return vector.x;}
float Vec2::y(){return vector.y;}

float& Vec2::getX(){return vector.x;}
float& Vec2::getY(){return vector.y;}