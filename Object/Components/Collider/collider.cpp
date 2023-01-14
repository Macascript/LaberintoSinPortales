#include "collider.h"
#include "../../../engine/datatypes/vertex.h"

Box2D::Box2D(){

}

bool Box2D::collision(BV* _b2){
	Box2D* b2=(Box2D*)_b2;
	
        if((xMin<b2->xMax && xMin>b2->xMin)&&(yMin<b2->yMax && yMin>b2->yMin)) return true;
        if((xMin<b2->xMax && xMin>b2->xMin)&&(yMax<b2->yMax && yMax>b2->yMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMin<b2->yMax && yMin>b2->yMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMax<b2->yMax && yMax>b2->yMin)) return true;
	
	return false;
}

bool Box2D::collisionPoint(Vec2 v2)
{
	Vec2 newV = Vec2(v2.x()/windowWidth, (windowHeight - v2.y())/windowHeight);
    std::cout<<"PROBANDO COLISIONES: "<<xMin<<" <= "<<newV.x()<<" <= "<<xMax<<"?? y... "<<yMin<<" <= "<<newV.y()<<" <= "<<yMax<<" ??"<<std::endl;
    //std::cout<<"PROBANDO COLISIONES: "<<newV.x()<<" , "<<newV.y()<<") frente a: ("<<xMin<<" , "<< xMax <<") , ("<<yMin<<" , "<<yMax<<")"<<std::endl;
	return (xMin <= newV.x() && yMin <= newV.y()) && (xMax >= newV.x() && yMax >= newV.y());
}

void Box2D::init(Object* obj,int triangleIdx){
	this->obj=obj;
	this->triangleIdx = triangleIdx;
	update();
}

void Box2D::update(){
	
		std::vector<vertex_t>* vertexlist = ((Mesh*)obj->getComponent("mesh"))->vertexList;
		std::vector<int>* facelist = ((Mesh*)obj->getComponent("mesh"))->faceList;
		obj->transform->computeMatrix();
        
		//Mat4 m = obj->transform->getMatrix();
        Mat4 v2 = obj->transform->getMatrix(); // rectTransform
		//int numvertex=vertexlist->size();
		Vec4 newpos;

        vertex_t v=vertexlist->data()[facelist->data()[triangleIdx *3]];    
        
        newpos = v2 * v.posicion;// multiplicar por escalar¿?

        xMin=xMax=newpos.x();
        yMin=yMax=newpos.y();

		for(int idv=(triangleIdx *3)+1; idv<((triangleIdx *3)+3); idv++)
		{   
			vertex_t v=vertexlist->data()[facelist->data()[idv]];
			newpos = v2 * v.posicion;// multiplicar por escalar¿?
			
			if(xMin>newpos.x())xMin=newpos.x();
			else if(xMax<newpos.x())xMax=newpos.x();
			
			if(yMin>newpos.y())yMin=newpos.y();
			else if(yMax<newpos.y())yMax=newpos.y();
		}

		yMin = ((yMin + 4.02505f) / 8.01599f);
		yMax = ((yMax + 4.02505f) / 8.01599f);
		xMin = ((xMin + 5.34855f) / 10.68f);
		xMax = ((xMax + 5.34855f) / 10.68f);
}

Collider::Collider(Object* obj)
{
    type = "collider";
	boxList=new std::vector<BV*>();
	int numtriangles=((Mesh*)obj->getComponent("mesh"))->faceList->size() / 3;
	//newbox->init(obj);
	for(int i=0;i<numtriangles;i++)
	{	
		BV* newbox=new Box2D();
		newbox->init(obj, i);
		boxList->push_back(newbox);
	}	
}
	
void Collider::update(){
	for(auto it= boxList->begin();it!= boxList->end();it++)
		(*it)->update();	
}

bool Collider::collision(Collider* c2){
        auto it1= boxList->begin();

        bool collision=false;
        while(!collision && it1!= boxList->end())
		{
			auto it2=c2->boxList->begin();
			while(!collision && it2!=c2->boxList->end())
			{
		        collision=(*it1)->collision(*it2)||(*it2)->collision(*it1) ;
				it2++;
			}
			it1++;		
        }
        return collision;	
}

bool Collider::collisionPoint(Vec2 v2)
{
    std::cout<<boxList->size()<<std::endl;
	auto it1 = boxList->begin();

	bool collision = false;
	while (!collision && it1 != boxList->end())
	{
		collision = (*it1)->collisionPoint(v2);
		it1++;
	}
	return collision;
}
