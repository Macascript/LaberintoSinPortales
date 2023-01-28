#pragma once

class MeshCollider;
#include "../../../engine/datatypes/vertex.h"
#include "../Mesh/mesh.h"
#include "boxCollider.h"
#include "collider.h"
#include "sphereCollider.h"

class Collider;
class BoxCollider;
class SphereCollider;
class Object;

class BV{

public:
		virtual bool collision(BV* b2)=0;
		virtual bool collisionPoint(Vec2 v2)=0;
		virtual void init(Object* obj,int triangleIdx)=0;
		virtual void update()=0;
};

class Box2D: public BV
{
public:
		//glm::vec3 position=glm::vec3(0,0,0);//esquina inferior izquierda
		float xMax=0;
		float yMax=0;
		float yMin=0;
		float xMin=0;
		Object* obj=nullptr;
		int triangleIdx;
		Box2D();
		bool collision(BV* b2);
		bool collisionPoint(Vec2 v2);
		void init(Object* obj, int triangleIdx);
		void update() override;
};

class Box3D: public BV
{
public:
		//glm::vec3 position=glm::vec3(0,0,0);//esquina inferior izquierda
		Vec4 ver1 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
		Vec4 ver2 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
		Vec4 ver3 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
		float planeA = 0.0f;
		float planeB = 0.0f;
		float planeC = 0.0f;
		float planeD = 0.0f;
		Object* obj=nullptr;
		int triangleIdx;
		Box3D();
		bool collision(BV* b2);
		bool collisionPoint(Vec2 v2);
		void init(Object* obj, int triangleIdx);
		void update() override;
};
// class Nodo{
// 	Nodo* hijoIzquierd = nullptr;
// 	Nodo* hijoDerecho = nullptr;

// };

class MeshCollider: public Collider{

public:
	std::vector<BV*> *boxList;
	MeshCollider(Object* obj);
	void update() override;
	bool collision(Collider* c2) override;
	bool collisionPoint(Vec2 v2) override;
private:
	bool collisionMesh(MeshCollider* c2);
	bool collisionBox(BoxCollider* c2);
	bool collisionSphere(SphereCollider* c2);
};
