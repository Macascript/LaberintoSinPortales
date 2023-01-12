#pragma once
#include "input.h"
#include "../Commons/common_opengl.h"

void updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateMouse(GLFWwindow* window, int button, int action, int mods);

void Input::init(Window* window) {
	input->window = window;

	memset(input->keys, 0, sizeof(bool) * 512);
	input->keys[512] = { false };

	memset(input->mouseKeys, 0, sizeof(bool) * 8);
	input->mouseKeys[8] = { false };

	/*memset(mouseKeysDown, 0, sizeof(char) * 8);
	mouseKeysDown[8] = { false };*/

	glfwSetKeyCallback((GLFWwindow*)window->getWindow(), updateKeys);
	glfwSetMouseButtonCallback((GLFWwindow*)window->getWindow(), updateMouse);
}

void Input::setKey(int key, bool active){
	input->keys[key] = active;
}

void Input::setMouseKey(int key, bool active) {
	input->mouseKeys[key] = active;
}

void updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	switch (action) {
		case GLFW_PRESS:
			Input::setKey(key,true);
			break;

		case GLFW_RELEASE:
			Input::setKey(key,false);
			break;
	}
}

bool Input::getKey(int i){
    if (i < 0 || i >= KEYS_TAM){
        std::cout<<"ERROR: Key "<<i<<" doesn't exist"<<std::endl;
        return false;
    }
    return input->keys[i];
}

bool Input::getMouseKey(int i) {
	if (i < 0 || i >= MOUSE_KEYS_TAM) {
		std::cout << "ERROR: Mouse Key " << i << " doesn't exist" << std::endl;
		return false;
	}
	return input->mouseKeys[i];
}

//bool Input::getMouseKeyDown(int i) {
//	if (i < 0 || i >= MOUSE_KEYS_TAM) {
//		std::cout << "ERROR: Mouse Key " << i << " doesn't exist" << std::endl;
//		return false;
//	}
//	return mouseKeys[i];
//}

Input* Input::getInput(){
	if(input == nullptr) input = new Input();
	
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
	switch (action) {
	case GLFW_PRESS:
		//Input::setMouseKeyDown(key, !getMouseKeyDown(key));
		Input::setMouseKey(button, true);
		break;

	case GLFW_RELEASE:
		Input::setMouseKey(button, false);
		break;
	}
}