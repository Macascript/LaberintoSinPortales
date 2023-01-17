#pragma once

#include "text.h"

Text::Text(std::string texto)
{
    init(texto, defaultTextFontSize, defaultTextFont, defaultTextvShader, defaultTextfShader, defaultTextFontColor);
}

Text::Text(std::string texto, float fontSize, Vec3 color)
{
    init(texto, fontSize, defaultTextFont, defaultTextvShader, defaultTextfShader, color);
}

Text::Text(std::string texto, float fontSize, std::string font_name, std::string textvShader, std::string textfShader, Vec3 color)
{
    init(texto, fontSize, font_name, textvShader, textfShader, color);
}

void Text::init(std::string texto, float fontSize, std::string font_name, std::string textvShader, std::string textfShader, Vec3 color)
{
    type = "text";
    this->text = texto;
    this->fontSize = fontSize;
    this->shader = new Shader(textvShader, textfShader);
    this->color = color;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
    glUseProgram(shader->programID);
    glUniformMatrix4fv(glGetUniformLocation(shader->programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    /*if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
    }*/

    if (FT_New_Face(ft, font_name.c_str(), 0, &font))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    else 
    {
        FT_Set_Pixel_Sizes(font, 0, fontSize);
        loadCharactersToMap(font);
    }

    

    /*if (FT_Load_Char(font, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return -1;
    }*/

    FT_Done_Face(font); //liberador de espacio
    FT_Done_FreeType(ft);//Destructor
}

void Text::loadCharactersToMap(FT_Face font) 
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(font, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            font->glyph->bitmap.width,
            font->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            font->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
            glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
            font->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
}

void Text::changeText(std::string newText) {
    this->text = newText;
}