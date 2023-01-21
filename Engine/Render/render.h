#pragma once
#include "../../Scene/scene.h"
#include "../Datatypes/vertex.h"
#include "../../Object/Components/Mesh/mesh.h"
#include "../../Object/Components/Text/text.h"

typedef struct bufferObject_t {
	unsigned int abo; //array buffer object ID
	unsigned int vbo; //vertex bufferObject
	unsigned int ibo; //idx bufferObje

}bufferObject_t;

class Render {
private:
	Mat4 view = Mat4(1.0f);
	Mat4 proj = Mat4(1.0f);
	std::map<int, bufferObject_t> boList;
	
	void drawObject(Object* obj, Scene* scene);
	void drawObjectUI(Object* obj, Scene* scene);
	void drawText(Object* text);
	void drawTextUI(Object* text);

public:
    Render();
	//void update();
	void drawScene(Scene* scene);
    //void initObj(Object* obj);
	void setupObject(Object* object);
	void setupText(Object* text);
};