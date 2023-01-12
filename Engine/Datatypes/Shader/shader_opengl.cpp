#pragma once
#include "shader.h"
#include "../../Commons/common_opengl.h"

Shader::Shader(std::string vshader, std::string fshader){

	this->vshader=vshader;
	this->fshader=fshader;
	
	compileShaders();
}

std::string Shader::readFile(std::string fileName) {
	std::ifstream inFile;
	inFile.open(fileName); //open the input file

	std::stringstream strStream;
	strStream << inFile.rdbuf(); //read the file

	std::string str = strStream.str(); //str holds the content of the file
	return str;

}

void Shader::checkCompileError(unsigned int program)
{

	GLint retCode;
	char errorLog[1024];
	glGetShaderiv(program, GL_LINK_STATUS, &retCode);
	if ( retCode == GL_FALSE ) {
		glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
		std::cout<<errorLog<<std::endl;
	}

}


void Shader::checkLinkError(unsigned int program)
{

	GLint retCode;
	char errorLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &retCode);
	if ( retCode == GL_FALSE ) {
		glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
		std::cout<<errorLog<<std::endl;
	}

}


void Shader::compileShaders(){


	this->programID = glCreateProgram();
	std::string vertexCode=readFile(vshader);
	std::string fragmentCode=readFile(fshader);
	
	const char* v=vertexCode.c_str();
	const char* f=fragmentCode.c_str();

	int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID , 1, &v, nullptr);
	glCompileShader(vertexShaderID );
	
	checkCompileError(vertexShaderID);
	
	int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID , 1, &f, nullptr);
	glCompileShader(fragmentShaderID );
	
	checkCompileError(fragmentShaderID);
	
	glAttachShader(programID, vertexShaderID );
	glAttachShader(programID, fragmentShaderID );
	
	glLinkProgram(programID);
	
	checkLinkError(programID);

}
