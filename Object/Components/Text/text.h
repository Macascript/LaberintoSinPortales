#pragma once 

#include "../../../Engine/Commons/common.h"
#include "../../../Engine/Commons/common_opengl.h"
#include "../../../Engine/Datatypes/Shader/shader.h"
#include "../../component.h"
#include "../../../Scene/scene.h"

#define defaultTextvShader ".\\Engine\\Datatypes\\Shader\\textvshader.glsl"
#define defaultTextfShader ".\\Engine\\Datatypes\\Shader\\textfshader.glsl"
#define defaultTextFont ".\\Object\\Components\\Text\\Raleway-BlackItalic.ttf"
#define defaultTextFontSize 48.0f
#define defaultTextFontColor Vec3(0,0,0)

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Text : public Component{

public:
    std::string text = "Esto son patatas";
    Shader* shader;
    Vec3 color;
    float fontSize;

	FT_Face font;
    std::map<char, Character> Characters;

    Text(std::string texto);
    Text(std::string texto, float fontSize, Vec3 color);
    Text(std::string texto, float fontSize, std::string font, std::string textvShader, std::string textfShader, Vec3 color);
    void init(std::string texto, float fontSize, std::string font_name, std::string textvShader, std::string textfShader, Vec3 color);
    void loadCharactersToMap(FT_Face font);
};