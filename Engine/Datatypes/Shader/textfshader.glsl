#version 330 core
in vec2 TexCoords;
out vec4 color;
float cutoff = 0.1;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 textureColor = texture(text, TexCoords);

    if(textureColor.r == 0 && textureColor.g == 0 && textureColor.b == 0)
        discard;
    else
    {
         vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
         color = vec4(textColor, 1.0) * sampled;
    }
}