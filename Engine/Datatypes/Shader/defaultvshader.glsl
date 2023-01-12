#version 430

layout(location=0) uniform mat4 MVP;
layout(location=1) uniform mat4 M;

layout(location=0)in vec4 vpos;
layout(location=1)in vec4 vcolor;
layout(location=2)in vec4 vnorm;
layout(location=3)in vec2 vtext;

out vec4 fcolor;
out vec4 fpos;
out vec4 fnorm;
out vec2 ftext;

void main() {
	gl_Position=MVP*vpos;
	fpos=M*vpos;
	fnorm=inverse(transpose(M))*vnorm;
	
	fcolor = vcolor;

	ftext = vtext;
}
