#pragma once
#include "../../../Engine/Datatypes/Utils/utils.h"

class Transform {
private:
    Mat4 modelMatrix = Mat4(1.0f);
public:
    bool isCanvas;
    Vec3 position = Vec3(0, 0, 0);
    Vec3 rotation = Vec3(0, 0, 0);
    Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);

    Transform(bool isCanvas = false);

    void update();
    Mat4 getMatrix();
    void computeMatrix();
};