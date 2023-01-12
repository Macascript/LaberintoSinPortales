#pragma once

#include "../../../Engine/Commons/common.h"
#include "../../../Engine/Datatypes/vertex.h"
#include "../../../Engine/Datatypes/Shader/shader.h"
#include "../../component.h"
#include "../../../Engine/Datatypes/Texture/texture.h"

#define defaultModel ".\\Object\\Components\\Mesh\\defaultmodel.trg"
#define defaultuiModel ".\\Object\\Components\\Mesh\\defaultuimodel.trg"
#define defaultVshader ".\\Engine\\Datatypes\\Shader\\defaultvshader.glsl"
#define defaultFshader ".\\Engine\\Datatypes\\Shader\\defaultfshader.glsl"
#define guiVshader ".\\Engine\\Datatypes\\Shader\\defaultguivshader.glsl"
#define guiFshader ".\\Engine\\Datatypes\\Shader\\defaultguifshader.glsl"
#define defaultTexture ".\\Engine\\Datatypes\\Texture\\defaulttexture.png"

class Mesh : public Component {
public:
    //atributos
    std::vector<vertex_t>* vertexList = nullptr;
    std::vector<int>* faceList = nullptr;
    Shader* shader = nullptr;
    Texture* texture = nullptr;
    //métodos
    Mesh();
    //Mesh(std::string modelFileName);
    Mesh(std::string modelFileName, std::string vShaderFilename, std::string fShaderFilename, std::string textureFilename);
    ~Mesh();
    void setTexture(std::string filename);
    void setShader(std::string filenamev, std::string filenamef);
    void loadFromFile(std::string modelFileName, std::string vShaderFilename, std::string fShaderFilename, std::string textureFilename);
    void setColor(int idxVertex, Vec4 color);
    void update();
};