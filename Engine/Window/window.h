#pragma once

#include "../Commons/common.h"
#include "../Input/input.h"

class Input;

class Window{
private:
    void* window;
public:
    Window(int resolutionX, int resolutionY, const char* title);
    // init(int resolutionX, int resolutionY,std::string title);
    void* getWindow();
    bool renderfps(double framerate);
    bool stillAlive();
    int getWindowWidth();
    int getWindowHeight();
    void update();
    //void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};