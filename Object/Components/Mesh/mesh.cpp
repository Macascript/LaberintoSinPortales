#include "mesh.h"

Mesh::Mesh() {
	type = "mesh";
	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();
	//añadir vértices
	loadFromFile(defaultModel, defaultVshader, defaultFshader, defaultTexture);
	// 	type = "mesh";
	// // 	vertexList=new std::vector<vertex_t>();
	// // 	faceList=new std::vector<int>();
	// // //añadir vértices

	// // 	vertex_t v1,v2,v3;

	// // 	v1.posicion=Vec4(-0.5f,-0.5,0.0f,1.0f);
	// // 	v2.posicion=Vec4( 0.0f, 0.5,0.0f,1.0f);
	// // 	v3.posicion=Vec4( 0.5f,-0.5,0.0f,1.0f);

	// // 	vertexList->push_back(v1);
	// // 	vertexList->push_back(v2);
	// // 	vertexList->push_back(v3);

	// // 	faceList->push_back(0);
	// // 	faceList->push_back(1);
	// // 	faceList->push_back(2);
}

Mesh::Mesh(std::string modelFileName, std::string vShaderFilename, std::string fShaderFilename, std::string textureFilename) {
	type = "mesh";
	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();
	//añadir vértices
	loadFromFile(modelFileName, vShaderFilename, fShaderFilename, textureFilename);
}

void Mesh::setColor(int idxVertex, Vec4 color) {
	(*vertexList)[idxVertex].color = color;
}

void Mesh::loadFromFile(std::string modelFileName, std::string vShaderFilename, std::string fShaderFilename, std::string textureFilename) {
	std::ifstream fin;
	fin.open(modelFileName);

	int numVertex = 0;
	fin >> numVertex;
	for (int i = 0; i < numVertex; i++)
	{
		vertex_t v1;
		fin >> v1.posicion.getX();
		fin >> v1.posicion.getY();
		fin >> v1.posicion.getZ();
		fin >> v1.posicion.getW();
		fin >> v1.color.getX(); //r
		fin >> v1.color.getY(); //g
		fin >> v1.color.getZ(); //b
		fin >> v1.color.getW(); //a

		fin >> v1.normal.getX();
		fin >> v1.normal.getY();
		fin >> v1.normal.getZ();
		fin >> v1.normal.getW();

		fin >> v1.texCoord.getX();
		fin >> v1.texCoord.getY();

		vertexList->push_back(v1);
	}
	int numFaces = 0;
	fin >> numFaces;
	for (int i = 0; i < numFaces; i++)
	{
		int v1, v2, v3;
		fin >> v1;
		fin >> v2;
		fin >> v3;
		faceList->push_back(v1);
		faceList->push_back(v2);
		faceList->push_back(v3);
	}

	// std::string vshader;
	// fin>>vshader;
	// std::string fshader;
	// fin>>fshader;
	// std::string textureFile;
	// fin>>textureFile;
	// std::string vshader = vShaderFilename;
	// std::string fshader = fShaderFilename;
	// std::string textureFile = textureFilename;

	/*if (vShaderFilename == "default") {
		vshader = ".\\Engine\\Datatypes\\Shader\\defaultguivshader.glsl";
	}
	else {
		vshader = vShaderFilename;
	}

	if (fShaderFilename == "default") {
		fshader = ".\\Engine\\Datatypes\\Shader\\defaultguifshader.glsl";
	}
	else {
		fshader = fShaderFilename;
	}

	if (textureFilename == "default") {
		textureFile = ".\\Engine\\Datatypes\\Texture\\defaulttexture.png";
	}
	else {
		textureFile = textureFilename;
	}*/

	/*std::string vshader = ".\\Engine\\Datatypes\\Shader\\defaultguivshader.glsl";
	std:: string fshader = ".\\Engine\\Datatypes\\Shader\\defaultguifshader.glsl";
	std::string textureFile = ".\\Engine\\Datatypes\\Texture\\defaulttexture.png";*/

	fin.close();

	shader = new Shader(vShaderFilename, fShaderFilename);
	if (textureFilename != "")
		texture = new Texture(textureFilename);
}

void Mesh::setTexture(std::string name) {
	if (texture != nullptr)
		delete texture;
	texture = new Texture(name);
}
void Mesh::setShader(std::string vname, std::string fname) {
	if (shader != nullptr)
		delete shader;
	shader = new Shader(vname, fname);
}

Mesh::~Mesh() {
	delete vertexList;
	delete faceList;
	delete shader;
	delete texture;
}

void Mesh::update() {}

void Mesh::setTexture(Texture* texture){
	if (this->texture != nullptr)
		delete this->texture;
	this->texture = texture;
}