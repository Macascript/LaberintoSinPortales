#version 430

layout(location=2) uniform vec4 lightPos;
layout(location=3) uniform vec4 eyePos;
layout(location=4) uniform sampler2D texture;
layout(location=5) uniform float maskPercentage;
layout(location=6) uniform vec2 scroll;

in vec4 fcolor;
in vec4 fpos;
in vec4 fnorm;
in vec2 ftext;

out vec4 gli_FragColor;

void main() {
	vec4 finalColor = fcolor;

	vec4 textColor = texture2D(texture,ftext+scroll);
	
	finalColor = maskPercentage * textColor + (1.0 - maskPercentage) * finalColor;
			
	gli_FragColor = finalColor;

}
