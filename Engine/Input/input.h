#pragma once
#include "../Window/window.h"
#include "../Datatypes/Utils/utils.h"

#define KEYS_TAM 512
#define MOUSE_KEYS_TAM 8

class Input {
private:
	static Input* input;
	bool* keys = new bool[512];
	bool* mouseKeys = new bool[8];
	Window* window;

public:

	static void init(Window* window);
	static void setKey(int key, bool active);
	static void setMouseKey(int key, bool active);
	static bool getKey(int i);
	static bool getMouseKey(int i);
	static Input* getInput();
	static Vec2 getMousePosition();
};