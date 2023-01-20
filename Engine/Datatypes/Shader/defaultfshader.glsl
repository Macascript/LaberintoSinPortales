#version 430

//struct Light
//{
//  vec3 eyePosOrDir;
//  bool isDirectional;
//  vec3 intensity;
//  float attenuation;
//} variableName;

layout(location=2) uniform int lightArraySize;
layout(location=3) uniform vec4 eyePos;
layout(location=4) uniform sampler2D texture;
layout(location=5) uniform float maskPercentage;
layout(location=6) uniform vec2 scroll;
layout(location=7) uniform vec4[100] lightPos;

in vec4 fcolor;
in vec4 fpos;
in vec4 fnorm;
in vec2 ftext;

out vec4 gli_FragColor;

void main() {

	vec4 eyeDir = normalize(eyePos - fpos);

	float Id = 0.5f;
	float kd = 0.5f;
	float Is = 0.1f;
	float ks = 0.1f;
	float powSpecular = 3f;
	float amb = 0.175f;

	
	float IdifusaTotal = 0;
	float IespecularTotal = 0;
	float auxDot = 0;
	vec4 auxLightDir = vec4(0.0);
	vec4 auxReflectedDir = vec4(0.0);

	for(int i = 0; i < lightArraySize; ++i)
	{
		auxLightDir = normalize(lightPos[i] - fpos);
		auxDot = max(dot(auxLightDir,fnorm),0.0f);
		IdifusaTotal += Id * kd * auxDot;
		
		if(auxDot > 0)
			auxReflectedDir = 2 * fnorm * (dot(auxLightDir,fnorm)) - auxLightDir;
			IespecularTotal += Is * ks * pow(max(dot(auxReflectedDir,eyeDir),0.0f),powSpecular);
	}

	vec4 textColor = texture2D(texture,ftext+scroll);
	vec4 finalColor = maskPercentage * textColor + (1.0 - maskPercentage) * fcolor;


	gli_FragColor = finalColor * (amb + IdifusaTotal + IespecularTotal);
	gli_FragColor.w = textColor.w;
}