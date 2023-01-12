#pragma once

#include "button.h"

void Button::onClick() 
{

}

void Button::update()
{
	Vec2 mousePosition;
	if (Input::getKey(0))
	{
		mousePosition = Input::getMousePosition();
	}
}