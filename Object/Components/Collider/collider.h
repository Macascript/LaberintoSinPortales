#pragma once

#include "../../component.h"

class Object;
class Component;
class UI;

class Collider : public Component {
public:
	virtual bool collision(Collider* c2) = 0;
	virtual bool collisionPoint(Vec2 v2) = 0;
};

