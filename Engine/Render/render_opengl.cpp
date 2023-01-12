#pragma once
#include "render.h"

#include "../Commons/common_opengl.h"

Render::Render() {
}

//void Render::drawScene(Scene* scene) {
//	// glDisable(GL_DEPTH_TEST);
//	// drawSkybox();
//	glEnable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}

void Render::setupObject(Object* object)
{

	bufferObject_t bo;
	glGenVertexArrays(1, &bo.abo);
	glBindVertexArray(bo.abo);
	
	glGenBuffers(1,&bo.vbo);
	glGenBuffers(1,&bo.ibo);

	glBindBuffer(GL_ARRAY_BUFFER,bo.vbo);

	/*if (object->getComponent("mesh") != nullptr){
		std::cout<<"CAGOENDIOS de render_opengl.cpp 1: "<<((Mesh*) object->getComponent("mesh"))->getType()<<std::endl;
		std::cout<<"CAGOENDIOS de render_opengl.cpp 1: "<<((Mesh*) object->getComponent("mesh"))->vertexList->size()<<std::endl;
	}else
		std::cout<<"PATATA de render_opengl.cpp 1"<<std::endl;*/

	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_t)*((Mesh*) object->getComponent("mesh"))->vertexList->size(),
	((Mesh*) object->getComponent("mesh"))->vertexList->data(),GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bo.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*((Mesh*) object->getComponent("mesh"))->faceList->size(),
	((Mesh*) object->getComponent("mesh"))->faceList->data(),GL_STATIC_DRAW);

	boList[object->getId()]=bo;
}

void Render::drawObject(Object* obj,Scene* scene){
	obj->transform->computeMatrix();
	
	bufferObject_t bo=boList[obj->getId()];
	
	glBindVertexArray(bo.abo);
	glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.ibo);


	glUseProgram(((Mesh*) obj->getComponent("mesh"))->shader->programID);
	unsigned int vpos=0;
	glEnableVertexAttribArray(vpos);
	glVertexAttribPointer(vpos,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,posicion));

	unsigned int vcolor=1;
	glEnableVertexAttribArray(vcolor);
	glVertexAttribPointer(vcolor,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,color));

	unsigned int vnorm=2;
	glEnableVertexAttribArray(vnorm);
	glVertexAttribPointer(vnorm,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,normal));

	unsigned int vtext = 3;
	glEnableVertexAttribArray(vtext);
	glVertexAttribPointer(vtext,2,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,texCoord));

	Camera* cam;

	/*if (!obj->getComponent("ui")) 
	{*/
		cam = scene->getCamera();
		
	/*}	
	else {
		cam = new Camera(Vec3(0, 0, 1.0f), Vec3(0, 0, -3.0f), ortho);
	}*/

	glm::vec4 camPos(0.0f);

	glm::mat4 MV = glm::translate(glm::mat4(1.0f), obj->transform->position.getVector());
	MV = glm::rotate(MV, obj->transform->rotation.x(), glm::vec3(1.0f, 0, 0));
	MV = glm::rotate(MV, obj->transform->rotation.y(), glm::vec3(0, 1.0f, 0));
	MV = glm::rotate(MV, obj->transform->rotation.z(), glm::vec3(0, 0, 1.0f));

	camPos = glm::vec4(cam->position.getVector(), 1.0f);
	

	//if (obj->getComponent("ui")) 
	//{
	//	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(640), 0.0f, static_cast<float>(480));
	//	glUniformMatrix4fv(glGetUniformLocation(((Mesh*)obj->getComponent("mesh"))->shader->programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, ((Mesh*)obj->getComponent("mesh"))->faceList->size(), ((Mesh*)obj->getComponent("mesh"))->faceList);
	//	//glUniformMatrix4fv(0, 1, GL_FALSE, &(projection * obj->transform->getMatrix().getMatrix())[0][0]);
	//}
	//else 
	//{
	if (!obj->getComponent("ui")) 
	{
		glUniformMatrix4fv(0, 1, GL_FALSE, &(proj.getMatrix() * view.getMatrix() * obj->transform->getMatrix().getMatrix())[0][0]);
		//glUniformMatrix4fv(1, 1, GL_FALSE, &(obj->transform->getMatrix().getMatrix())[0][0]);
	}
	else 
	{
		//Mat4 projection = cam->getProjectionMatrix();
		//glUniformMatrix4fv(0, 1, GL_FALSE, &(projection.getMatrix())[0][0]);
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(640), 0.0f, static_cast<float>(480));
		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(proj.getMatrix() * obj->transform->getMatrix().getMatrix()));
		//glUniformMatrix4fv(1, 1, GL_FALSE, &(obj->transform->position.getVector())[0]);
	}

	glUniformMatrix4fv(1, 1, GL_FALSE, &(obj->transform->getMatrix().getMatrix())[0][0]);
	//glUniform4fv(2,1,&glm::vec4(((*scene->getLights())[0]->position),1.0f)[0]);
	glUniform4fv(3, 1, &camPos[0]);
	//}

	int textureUnit = 0;
	glUniform1i(4,textureUnit);
	((Mesh*) obj->getComponent("mesh"))->texture->bind(textureUnit);

	glUniform1f(5,1.0);

	// if (obj->typeObject == BACKGROUND_OBJ){
	// 	Background* bg = (Background*) obj;
	// 	glUniform2fv(6,1,&bg->scroll[0]);
	// }else{
		glUniform2fv(6,1,&glm::vec2(0.0f,0.0f)[0]);
	// }
	
	//glUniform4fv(7,1,&glm::vec4(((*scene->getLights())[1]->position),1.0f)[0]);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	//glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*if (obj->getComponent("mesh") != nullptr){
		std::cout<<"CAGOENDIOS de render_opengl.cpp 2: "<<((Mesh*) obj->getComponent("mesh"))->getType()<<std::endl;
		std::cout<<"CAGOENDIOS de render_opengl.cpp 2: "<<((Mesh*) obj->getComponent("mesh"))->faceList->size()<<std::endl;
	}else
		std::cout<<"PATATA de render_opengl.cpp 2"<<std::endl;*/
	glDrawElements(GL_TRIANGLES, ((Mesh*) obj->getComponent("mesh"))->faceList->size(), GL_UNSIGNED_INT,nullptr);
	//if (obj->getComponent("ui")) delete cam;
}

void Render::setupText(Object* text) 
{
	bufferObject_t bo;

	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//unsigned int VAO, VBO;
	glGenVertexArrays(1, &bo.abo);
	glGenBuffers(1, &bo.vbo);
	//glGenBuffers(1, &bo.ibo);
	glBindVertexArray(bo.abo);
	glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.ibo);

	boList[text->getId()] = bo;
}

void Render::drawText(Object* text)
{
	// activate corresponding render state	
	Text* actualText = ((Text*)text->getComponent("text"));

	glUseProgram(actualText->shader->programID);
	glUniform3f(glGetUniformLocation(actualText->shader->programID, "textColor"), actualText->color.x(), actualText->color.y(), actualText->color.z());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(boList[text->getId()].abo);

	Vec3 oldPosition = text->transform->position;

	// iterate through all characters
	std::string::const_iterator c;
	for (c = actualText->text.begin(); c != actualText->text.end(); c++)
	{
		Character ch = actualText->Characters[*c];

		float xpos = text->transform->position.x() + ch.Bearing.x;
		float ypos = text->transform->position.y() - (ch.Size.y - ch.Bearing.y);

		float w = ch.Size.x;
		float h = ch.Size.y;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, boList[text->getId()].vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		text->transform->position = Vec3(text->transform->position.x() + (ch.Advance >> 6), text->transform->position.y(), text->transform->position.z()); // bitshift by 6 to get value in pixels (2^6 = 64)
		//x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	if (!text->getComponent("ui")) text->transform->position = oldPosition;
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//void Render::drawTextUI(Object* text)
//{
//	// activate corresponding render state	
//	Text* actualText = ((Text*)text->getComponent("text"));
//
//	glUseProgram(actualText->shader->programID);
//	glUniform3f(glGetUniformLocation(actualText->shader->programID, "textColor"), actualText->color.x(), actualText->color.y(), actualText->color.z());
//	glActiveTexture(GL_TEXTURE0);
//	glBindVertexArray(boList[text->getId()].abo);
//
//	// iterate through all characters
//	std::string::const_iterator c;
//	for (c = actualText->text.begin(); c != actualText->text.end(); c++)
//	{
//		Character ch = actualText->Characters[*c];
//
//		float xpos = text->transform->position.x() + ch.Bearing.x;
//		float ypos = text->transform->position.y() - (ch.Size.y - ch.Bearing.y);
//
//		float w = ch.Size.x;
//		float h = ch.Size.y;
//		// update VBO for each character
//		float vertices[6][4] = {
//			{ xpos,     ypos + h,   0.0f, 0.0f },
//			{ xpos,     ypos,       0.0f, 1.0f },
//			{ xpos + w, ypos,       1.0f, 1.0f },
//
//			{ xpos,     ypos + h,   0.0f, 0.0f },
//			{ xpos + w, ypos,       1.0f, 1.0f },
//			{ xpos + w, ypos + h,   1.0f, 0.0f }
//		};
//		// render glyph texture over quad
//		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//		// update content of VBO memory
//		glBindBuffer(GL_ARRAY_BUFFER, boList[text->getId()].vbo);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		// render quad
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//		text->transform->position = Vec3(text->transform->position.x() + (ch.Advance >> 6), text->transform->position.y(), text->transform->position.z()); // bitshift by 6 to get value in pixels (2^6 = 64)
//		//x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
//	}
//	glBindVertexArray(0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//}

void Render::drawScene(Scene* scene)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera* cam=scene->getCamera();
	std::map<int,Object*> *addedObjList=scene->addedObjectList;
	std::map<int,Object*> uiObjList;
	
	for(auto it=addedObjList->begin();
            it!=addedObjList->end();
            it++)
    {
		//std::cout<<"PATATA de render_opengl.cpp drawScene()"<<std::endl;
		if (it->second->getComponent("text"))
			setupText(it->second);
		else if(it->second->getComponent("mesh"))
			setupObject(it->second);
    }
    
	cam->computeMatrix();
	view=cam->getMatrix();
	proj=cam->getProjectionMatrix();
	std::map<int,Object*>* objList=scene->objectList;

	for (auto it = objList->begin();
		it != objList->end();
		it++)
	{
		if (it->second->getComponent("ui")){
			uiObjList[it->second->getId()] = it->second;
			continue;
		}
		if (it->second->getComponent("text"))
		{
			/*if(it->second->getComponent("ui")) drawTextUI(it->second);
			else */drawText(it->second);
		}
		else if (it->second->getComponent("mesh")) 
		{
			/*if (it->second->getComponent("ui")) drawObjectUI(it->second, scene);
			else */drawObject(it->second, scene);
		}	
	}

	for (auto it = uiObjList.begin();
		it != uiObjList.end();
		it++)
	{
		glDisable(GL_DEPTH_TEST);
		if (it->second->getComponent("text"))
			drawText(it->second);
		else if(it->second->getComponent("mesh"))
			drawObject(it->second, scene);
	}
}