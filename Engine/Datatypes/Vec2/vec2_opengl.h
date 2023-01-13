#pragma once
#include "../../Commons/common_opengl.h"

class Vec2 {
private:
    glm::vec2 vector = glm::vec2(0,0);

public:
    Vec2();
    Vec2(glm::vec2 vector);
    Vec2(float x, float y);
    glm::vec2 getVector();
    float x();
    float y();
    float& getX();
    float& getY();
};