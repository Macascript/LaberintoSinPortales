#pragma once

#include "button.h"

Button::Button(Object* obj){
	type = "button";
	collider = (Collider*) obj->getComponent("collider");
}

void Button::onClick() 
{
	std::cout<<"Me pulsaste!!!"<<std::endl;
}

void Button::update()
{
	if (Input::getMouseKeyDown(0))
	{
		Vec2 mousePosition;
		mousePosition = Input::getMousePosition();
		std::cout<<mousePosition.x()<<","<<mousePosition.y() << std::endl;
		if (collider->collisionPoint(mousePosition))
			onClick();
	}
}