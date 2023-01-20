#pragma once
#include "../../component.h"

class BoxCollider: public Component{

public:
    Vec3 offset;
	Vec3 bounds;
	BoxCollider();
	void update();
	bool collision(BoxCollider* c2);
	bool collisionPoint(Vec2 v2);
};