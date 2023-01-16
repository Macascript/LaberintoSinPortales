#pragma once

#include "../Window/window.h"
#include "../Datatypes/Utils/utils.h"
//#include "../../Scene/scene.h"

#define KEYS_TAM 512
#define MOUSE_KEYS_TAM 8

class Window;

class Input {
private:
	static Input* input;
	std::list<int>* pressedKeys = new std::list<int>();
	std::list<int>* pressedMouseKeys = new std::list<int>();
	bool* keys = new bool[512];
	bool* keysBefore = new bool[512];
	bool* mouseKeys = new bool[8];
	bool* mouseKeysBefore = new bool[8];
	Window* window;
	double lastFrame = glfwGetTime();
	double currentFrame = glfwGetTime();
	double deltaTime;
	float mouseSpeed = 20.0f;
	float speed = 1.0f;

public:

	static void init(Window* window);
	static void update();
	static void setKey(int key, bool active);
	static void setMouseKey(int key, bool active);

	static bool getKey(int i);
	static bool getKeyDown(int i);
	static bool getKeyUp(int i);

	static bool getMouseKey(int i);
	static bool getMouseKeyDown(int i);
	static bool getMouseKeyUp(int i);

	static Input* getInput();
	static Vec2 getMousePosition();

	static double getDeltaTime();
	static float getMouseSpeed();
	static float getSpeed();

	static void setMouseSpeed(float newSpeed);
	static void setSpeed(float newSpeed);
};