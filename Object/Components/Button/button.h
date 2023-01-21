#pragma once 

#include "../Collider/collider.h"

class Collider;
class Component;
class Object;

class Button:public Component 
{
private:
	Collider* collider;
	std::function<void()> onClick;
public:
	Button(Object* obj, std::function<void()> onClick);
	void update();
};