#pragma once
#include "input.h"
#include "../Commons/common_opengl.h"

void updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateMouse(GLFWwindow* window, int button, int action, int mods);

Input* Input::input = nullptr;

void Input::init(Window* window)
{
	input = new Input();
	input->window = window;

	memset(input->keys, 0, sizeof(bool) * 512);
	input->keys[512] = { false };

	memset(input->mouseKeys, 0, sizeof(bool) * 8);
	input->mouseKeys[8] = { false };

	memset(input->keysBefore, 0, sizeof(bool) * 512);
	input->keysBefore[512] = { false };

	memset(input->mouseKeysBefore, 0, sizeof(bool) * 8);
	input->mouseKeysBefore[8] = { false };

	glfwSetKeyCallback((GLFWwindow*)input->window->getWindow(), updateKeys);
	glfwSetMouseButtonCallback((GLFWwindow*)input->window->getWindow(), updateMouse);
}

void Input::setKey(int key, bool active)
{
	input->keysBefore[key] = input->keys[key];
	input->keys[key] = active;
	if (active){
		input->pressedKeys->push_back(key);
	}else{
		input->pressedKeys->remove(key);
	}
}

void Input::setMouseKey(int key, bool active)
{
	input->mouseKeysBefore[key] = input->mouseKeys[key];
	input->mouseKeys[key] = active;
	if (active){
		input->pressedMouseKeys->push_back(key);
	}else{
		input->pressedMouseKeys->remove(key);
	}
}

void updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	switch (action) {
		case GLFW_PRESS:
			Input::setKey(key,true);
			break;

		case GLFW_RELEASE:
			Input::setKey(key,false);
			break;
	}
}

bool Input::getKey(int i)
{
    if (i < 0 || i >= KEYS_TAM){
        std::cout<<"ERROR: Key "<<i<<" doesn't exist"<<std::endl;
        return false;
    }
    return input->keys[i];
}

bool Input::getKeyDown(int i)
{
    if (i < 0 || i >= KEYS_TAM){
        std::cout<<"ERROR: Key "<<i<<" doesn't exist"<<std::endl;
        return false;
    }
    return input->keys[i] && !input->keysBefore[i];
}

bool Input::getKeyUp(int i)
{
    if (i < 0 || i >= KEYS_TAM){
        std::cout<<"ERROR: Key "<<i<<" doesn't exist"<<std::endl;
        return false;
    }
    return !input->keys[i] && input->keysBefore[i];
}

bool Input::getMouseKey(int i)
{
	if (i < 0 || i >= MOUSE_KEYS_TAM) {
		std::cout << "ERROR: Mouse Key " << i << " doesn't exist" << std::endl;
		return false;
	}
	return input->mouseKeys[i];
}

bool Input::getMouseKeyDown(int i)
{
	if (i < 0 || i >= MOUSE_KEYS_TAM) {
		std::cout << "ERROR: Mouse Key " << i << " doesn't exist" << std::endl;
		return false;
	}
	// std::cout<<"Mouse key: "<<input->mouseKeys[i]<<" y Before: "<<input->mouseKeysBefore[i]<<std::endl;
	return input->mouseKeys[i] && !input->mouseKeysBefore[i];
}

bool Input::getMouseKeyUp(int i)
{
	if (i < 0 || i >= MOUSE_KEYS_TAM) {
		std::cout << "ERROR: Mouse Key " << i << " doesn't exist" << std::endl;
		return false;
	}
	return !input->mouseKeys[i] && input->mouseKeysBefore[i];
}

Input* Input::getInput()
{
	//if(input == nullptr) input = new Input();
	
	return input;
}

Vec2 Input::getMousePosition() 
{
	double xpos;
	double ypos;
	glfwGetCursorPos((GLFWwindow*)input->window->getWindow(), &xpos, &ypos);
	return Vec2(xpos, ypos);
}

void updateMouse(GLFWwindow* window, int button, int action, int mods) 
{
	// std::cout<<"updateMouse: "<<action<<std::endl;
	switch (action) {
	case GLFW_PRESS:
		Input::setMouseKey(button, true);
		break;

	case GLFW_RELEASE:
		Input::setMouseKey(button, false);
		break;
	}
}

void Input::update()
{
	for (auto it = input->pressedMouseKeys->begin(); it != input->pressedMouseKeys->end(); it++){
		input->mouseKeysBefore[*it] = input->mouseKeys[*it];
	}
	for (auto it = input->pressedKeys->begin(); it != input->pressedKeys->end(); it++){
		input->keysBefore[*it] = input->keys[*it];
	}
	
	input->currentFrame = glfwGetTime();
	input->deltaTime = input->currentFrame - input->lastFrame;
	input->lastFrame = input->currentFrame;

	//glfwGetCursorPos((GLFWwindow*)input->window->getWindow(), &input->mousePosX,&input->mousePosY);
	//glfwSetCursorPos((GLFWwindow*)input->window->getWindow(), 960 / 2, 720 / 2);
}

double Input::getDeltaTime()
{
	return input->deltaTime;
}

float Input::getMouseSpeed()
{
	return input->mouseSpeed;
}

float Input::getSpeed()
{
	return input->speed;
}