#pragma once
#include "window.h"

#include "../Commons/common_opengl.h"

Window::Window(int resolutionX, int resolutionY, const char* title){
    int glfwState = glfwInit();
	if (!glfwState)
		std::cout << "ERROR iniciando glfw\n";
    
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

    window = (void*) glfwCreateWindow(resolutionX,resolutionY,title, nullptr, nullptr); // (GLFWwindow*)
    glfwMakeContextCurrent((GLFWwindow*) window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	glClearColor(0, 0.6667f, 0.8941f, 1.0f);

    int glewState = glewInit();

	if (glewState != GLEW_OK)
		std::cout << "ERROR iniciando glew\n";
}

void* Window::getWindow(){
    return window;
}

int Window::getWindowWidth() {
	return windowWidth;
}

int Window::getWindowHeight() {
	return windowHeight;
}

bool Window::renderfps(double framerate){
    static double currentTime = 0;
	static double lastTime = 0;

	currentTime = glfwGetTime();
	if (currentTime - lastTime >= 1.0 / framerate)
	{
		lastTime = currentTime;
		return true;
	}
	return false;
}

bool Window::stillAlive(){
    return !glfwWindowShouldClose((GLFWwindow*) window);
}

void Window::update(){
    glfwSwapBuffers((GLFWwindow*) window);
	Input::update();
	glfwPollEvents();
}


//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}