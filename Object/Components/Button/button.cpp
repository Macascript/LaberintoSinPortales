#pragma once

#include "button.h"

Button::Button(Object* obj,std::function<void()> onClick){
	type = "button";
	collider = (Collider*) obj->getComponent("collider");
	this->onClick = onClick;
}

void Button::update()
{
	if (Input::getMouseKeyDown(0))
	{
		Vec2 mousePosition;
		mousePosition = Input::getMousePosition();
		//std::cout<<mousePosition.x()<<","<<mousePosition.y() << std::endl;
		if (collider->collisionPoint(mousePosition))
			onClick();
	}
}