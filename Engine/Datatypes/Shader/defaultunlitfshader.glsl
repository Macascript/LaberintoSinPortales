#version 430

layout(location=3) uniform vec4 eyePos;
layout(location=4) uniform sampler2D texture;
layout(location=5) uniform float maskPercentage;
layout(location=6) uniform vec2 scroll;
layout(location=7) uniform vec4 lightPos;

in vec4 fcolor;
in vec4 fpos;
in vec4 fnorm;
in vec2 ftext;

out vec4 gli_FragColor;

void main() {
	vec4 finalColor = fcolor;

	float amb=0.2f;
	float diffuse=0.0f;

	vec4 textColor = texture2D(texture,ftext+scroll);
	
	finalColor = maskPercentage * textColor + (1.0 - maskPercentage) * finalColor;

	vec4 lightDir=normalize(lightPos-fpos);
	vec4 reflectedDir=2*fnorm*(dot(lightDir,fnorm))-lightDir;
	vec4 eyeDir = normalize(eyePos-fpos);
	
	diffuse=max(dot(fnorm,lightDir),0.0f); //color luz
	
	float specular= pow(max(dot(eyeDir,reflectedDir), 0.0f),256);
	
    //gli_FragColor = (finalColor)*(amb+diffuse+specular);
	gli_FragColor = finalColor * 2.0f;
}