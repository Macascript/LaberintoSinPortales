#pragma once
class BoxCollider;
#include "../../component.h"
#include "../Camera/camera.h"
#include "meshCollider.h"
#include "collider.h"

class Collider;
class Camera;
class Object;
class MeshCollider;
class Component;

class BoxCollider: public Collider{
private:
	bool collisionMesh(MeshCollider* c2);
	bool collisionBox(BoxCollider* c2);
	Camera* camera;
public:
    Vec3 offset;
	Vec3 bounds;
	BoxCollider(Camera* camera);
    // void init();
	void update() override;
	bool collision(Collider* c2) override;
	bool collisionPoint(Vec2 v2) override;
};