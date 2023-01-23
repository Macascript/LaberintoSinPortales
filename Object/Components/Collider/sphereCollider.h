#pragma once

#include "../Camera/camera.h"
#include "collider.h"
#include "boxCollider.h"
#include "meshCollider.h"

class MeshCollider;
class SphereCollider;
class Collider;
class Camera;
class Object;
class Component;

class SphereCollider : public Collider {
private:
	bool collisionMesh(MeshCollider* c2);
	bool collisionBox(BoxCollider* c2);
	bool collisionSphere(SphereCollider* c2);
	Camera* camera;
	Vec3 center = gameObject->transform->position;
public:
	Vec3 offset = Vec3(0, 0, 0);
	float radius = 1.0f;
	SphereCollider(Camera* camera);
	// void init();
	void update() override;
	bool collision(Collider* c2) override;
	bool collisionPoint(Vec2 v2) override;
	Vec3 getCenter();
};