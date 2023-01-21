#pragma once
#include "../../component.h"
#include "../Camera/camera.h"
#include "collider.h"

class BoxCollider: public Collider{
public:
    Vec3 offset;
	Vec3 bounds;
	BoxCollider(Camera* camera);
    // void init();
	void update();
	bool collision(BoxCollider* c2);
	bool collisionPoint(Vec2 v2);
	Camera* camera;
};