#pragma once
#include "../../Commons/common.h"

class Shader{
public:
	unsigned int programID=0xFFFFFFFF;
	std::string vshader,fshader;
	
	void checkCompileError(unsigned int program);
	void checkLinkError(unsigned int program);
	
	Shader(std::string vshader, std::string fshader);
	
	std::string readFile(std::string fileName);
	
	void compileShaders();
	
};