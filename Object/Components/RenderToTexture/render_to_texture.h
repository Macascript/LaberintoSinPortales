#pragma once
#include "../../component.h"
#include "../Mesh/mesh.h"

class RenderToTexture: public Component {
private:
    unsigned int glFrameBufferId = 0;
    unsigned int depthrenderbuffer;
    Mesh* mesh;
public:
    RenderToTexture(Object* obj, int w, int h);
    void update();
};