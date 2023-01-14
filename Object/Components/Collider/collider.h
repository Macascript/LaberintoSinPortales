#pragma once

#include "../UI/ui.h"

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
		void update();
};

// class Nodo{
// 	Nodo* hijoIzquierd = nullptr;
// 	Nodo* hijoDerecho = nullptr;

// };

class Collider: public Component{

public:
	std::vector<BV*> *boxList;
	Collider(Object* obj);
	void update();
	bool collision(Collider* c2);
	bool collisionPoint(Vec2 v2);
};
