#pragma once
class BoxCollider;
#include "../../component.h"
#include "../Camera/camera.h"
#include "meshCollider.h"
#include "sphereCollider.h"
#include "collider.h"

class Collider;
class Camera;
class Object;
class MeshCollider;
class SphereCollider;
class Component;

class BoxCollider: public Collider{
private:
	bool collisionMesh(MeshCollider* c2);
	bool collisionBox(BoxCollider* c2);
	bool collisionSphere(SphereCollider* c2);
	Camera* camera;
public:
    Vec3 offset = Vec3(0, 0, 0);
	Vec3 bounds = Vec3(1.0f, 1.0f, 1.0f);
	BoxCollider(Camera* camera);
    // void init();
	void update() override;
	bool collision(Collider* c2) override;
	bool collisionPoint(Vec2 v2) override;
	bool collisionTriangle(BV* triangle);
};