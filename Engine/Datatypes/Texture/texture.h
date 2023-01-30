#pragma once
#include "../../Commons/common.h"

class Texture{
public:
    int w = 0;
    int h = 0;
    unsigned int glId = -1;

    Texture(int w, int h, unsigned int glId);
    Texture(std::string filename);
    void bind(int textureunitIdx);
};