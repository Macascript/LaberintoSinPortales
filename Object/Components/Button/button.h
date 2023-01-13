#pragma once 

#include "../Collider/collider.h"

class Collider;

class Button:public Component 
{
private:
	Collider* collider;
public:
	Button(Object* obj);
	void onClick();
	void update();
};