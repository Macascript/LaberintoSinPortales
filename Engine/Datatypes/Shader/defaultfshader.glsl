#version 430

struct Light
{
  vec4 lightPos;
  float intensityD;
  float reflectanceD;
  float intensityS;
  float reflectanceS;
  float shininessCoef;
  float intensityA;
  float reflectanceA;
  vec4 lightColor;
};

layout(location=2) uniform int lightArraySize;
layout(location=3) uniform vec4 eyePos;
layout(location=4) uniform sampler2D texture;
layout(location=5) uniform float maskPercentage;
layout(location=6) uniform vec2 scroll;
layout(location=7) uniform Light[100] lights;

in vec4 fcolor;
in vec4 fpos;
in vec4 fnorm;
in vec2 ftext;

out vec4 gli_FragColor;

void main() {

	vec4 eyeDir = normalize(eyePos - fpos);
	vec4 textColor = texture2D(texture,ftext+scroll);
	vec4 finalColor = maskPercentage * textColor + (1.0 - maskPercentage) * fcolor;

	float intensityD = 0;
	float reflectanceD = 0;
	float intensityS = 0;
	float reflectanceS = 0;
	float shininessCoef = 0;
	float intensityA = 0;
	float reflectanceA = 0;

	vec4 ambiental = vec4(0.0);
	vec4 diffuse = vec4(0.0);
	vec4 specular = vec4(0.0);

	
	vec4 IdifusaTotal = vec4(0.0);
	vec4 IespecularTotal = vec4(0.0);
	vec4 IambientalTotal = vec4(0.0);
	float auxDot = 0;
	vec4 auxLightDir = vec4(0.0);
	vec4 auxReflectedDir = vec4(0.0);

	for(int i = 0; i < lightArraySize; ++i)
	{
		intensityD = lights[i].intensityD;
		reflectanceD = lights[i].reflectanceD;
		intensityS = lights[i].intensityS;
		reflectanceS = lights[i].reflectanceS;
		shininessCoef = lights[i].shininessCoef;
		intensityA = lights[i].intensityA;
		reflectanceA = lights[i].reflectanceA;

		ambiental = intensityA * reflectanceA * lights[i].lightColor;
		diffuse = intensityD * reflectanceD * lights[i].lightColor;
		specular = intensityS * reflectanceS * lights[i].lightColor;

		IambientalTotal += ambiental;

		auxLightDir = normalize(lights[i].lightPos - fpos);
		auxDot = max(dot(auxLightDir,fnorm),0.0f);
		IdifusaTotal += diffuse * auxDot;
		
		if(auxDot > 0)
			auxReflectedDir = 2 * fnorm * (dot(auxLightDir,fnorm)) - auxLightDir;
			IespecularTotal += specular * pow(max(dot(auxReflectedDir,eyeDir),0.0f),shininessCoef);
	}

	gli_FragColor = finalColor * ((IambientalTotal/lightArraySize) + IdifusaTotal + IespecularTotal);
	gli_FragColor.w = finalColor.w;
}