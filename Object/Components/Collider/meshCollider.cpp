#include "meshCollider.h"


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
    //std::cout<<"PROBANDO COLISIONES: "<<xMin<<" <= "<<newV.x()<<" <= "<<xMax<<"?? y... "<<yMin<<" <= "<<newV.y()<<" <= "<<yMax<<" ??"<<std::endl;
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

Box3D::Box3D(){

}

bool Box3D::collision(BV* _b2){
	Box3D* b2=(Box3D*)_b2;
	
        /*if((xMin<b2->xMax && xMin>b2->xMin)&&(yMin<b2->yMax && yMin>b2->yMin)&&(zMin<b2->zMax && zMin>b2->zMin)) return true;
        if((xMin<b2->xMax && xMin>b2->xMin)&&(yMax<b2->yMax && yMax>b2->yMin)&&(zMax<b2->zMax && zMax>b2->zMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMin<b2->yMax && yMin>b2->yMin)&&(zMin<b2->zMax && zMin>b2->zMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMax<b2->yMax && yMax>b2->yMin)&&(zMax<b2->zMax && zMax>b2->zMin)) return true;

        if((xMin<b2->xMax && xMin>b2->xMin)&&(yMin<b2->yMax && yMin>b2->yMin)&&(zMax<b2->zMax && zMax>b2->zMin)) return true;
        if((xMin<b2->xMax && xMin>b2->xMin)&&(yMax<b2->yMax && yMax>b2->yMin)&&(zMin<b2->zMax && zMin>b2->zMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMin<b2->yMax && yMin>b2->yMin)&&(zMax<b2->zMax && zMax>b2->zMin)) return true;
        if((xMax<b2->xMax && xMax>b2->xMin)&&(yMax<b2->yMax && yMax>b2->yMin)&&(zMin<b2->zMax && zMin>b2->zMin)) return true;*/

		//if ((xMin<b2->xMax && xMax>b2->xMin) && (yMin<b2->yMax && yMax>b2->yMin) && (zMin<b2->zMax && zMax>b2->zMin)) return true;
	
	float ep1, ep2, t = 0.0f;
	float planeIntersectX, planeIntersectY, planeIntersectZ = 0.0f;
	Vec3 pointInPlane = Vec3(0.0f, 0.0f, 0.0f);

	Vec3 b2V[4];
	b2V[0] = b2->ver1;
	b2V[1] = b2->ver2;
	b2V[2] = b2->ver3;
	b2V[3] = b2->ver1;

	for (int k = 0; k < 3; k++)
	{
		ep1 = (planeA * b2V[k].x()) + (planeB * b2V[k].y()) + (planeC * b2V[k].z());
		ep2 = (planeA * b2V[k + 1].x()) + (planeB * b2V[k + 1].y()) + (planeC * b2V[k + 1].z());

		t = -1;

		if (ep1 != ep2)
			t = -(ep2 + planeD) / (ep1 - ep2);

		if (t >= 0.0f && t <= 1.0f)
		{
			planeIntersectX = (b2V[k].x() * t) + (b2V[k + 1].x() * (1 - t));
			planeIntersectY = (b2V[k].y() * t) + (b2V[k + 1].y() * (1 - t));
			planeIntersectZ = (b2V[k].z() * t) + (b2V[k + 1].z() * (1 - t));

			pointInPlane = Vec3(planeIntersectX, planeIntersectY, planeIntersectZ);

			if (PointInTriangle(ver1, ver2, ver3, pointInPlane))
			{
				return true;
			}
		}
	}

	return false;
}

bool PointInTriangle(Vec3 vertex1, Vec3 vertex2, Vec3 vertex3, Vec3 point)
{
	//primero calculamos el area del triangulo
	float distX = vertex1.x() - vertex2.x();
	float distY = vertex1.y() - vertex2.y();
	float distZ = vertex1.z() - vertex2.z();

	float edgeLength1 = sqrt(distX * distX + distY * distY + distZ * distZ);

	distX = vertex1.x() - vertex3.x();
	distY = vertex1.y() - vertex3.y();
	distZ = vertex1.z() - vertex3.z();

	float edgeLength2 = sqrt(distX * distX + distY * distY + distZ * distZ);

	distX = vertex2.x() - vertex3.x();
	distY = vertex2.y() - vertex3.y();
	distZ = vertex2.z() - vertex3.z();

	float edgeLength3 = sqrt(distX * distX + distY * distY + distZ * distZ);

	float s = (edgeLength1 + edgeLength2 + edgeLength3) / 2.0f;

	float mainTriArea = sqrt(s * (s - edgeLength1) * (s - edgeLength2) * (s - edgeLength3));

	//ahora inicializamos un nuevo array que contendrá las 3 areas de los triangulos generados con el punto de interseccion y los 3 vertices del triangulo
	float smallTriArea[3] = { 0.0f, 0.0f, 0.0f };
	Vec3 triVert[4];
	triVert[0] = vertex1;
	triVert[1] = vertex2;
	triVert[2] = vertex3;
	triVert[3] = vertex1; //When i=2, i+1 will be vertex1

	//Find 3 triangle areas using the plane intersecting point
	for (int i = 0; i < 3; i++)
	{
		distX = point.x() - triVert[i].x();
		distY = point.y() - triVert[i].y();
		distZ = point.z() - triVert[i].z();

		edgeLength1 = sqrt(distX * distX + distY * distY + distZ * distZ);

		distX = point.x() - triVert[i + 1].x();
		distY = point.y() - triVert[i + 1].y();
		distZ = point.z() - triVert[i + 1].z();

		edgeLength2 = sqrt(distX * distX + distY * distY + distZ * distZ);

		distX = triVert[i].x() - triVert[i + 1].x();
		distY = triVert[i].y() - triVert[i + 1].y();
		distZ = triVert[i].z() - triVert[i + 1].z();

		edgeLength3 = sqrt(distX * distX + distY * distY + distZ * distZ);

		s = (edgeLength1 + edgeLength2 + edgeLength3) / 2.0f;

		smallTriArea[i] = sqrt(s * (s - edgeLength1) * (s - edgeLength2) * (s - edgeLength3));
	}

	float totalSmallTriArea = smallTriArea[0] + smallTriArea[1] + smallTriArea[2];

	//Compare the three smaller triangle areas with the main triangles area
	//Subtract a small value from totalSmallTriArea to make up for inaccuracy
	if (mainTriArea >= (totalSmallTriArea - 0.001f))
	{
		return true;
	}

	return false;
}

bool Box3D::collisionPoint(Vec2 v2)
{
	Vec2 newV = Vec2(v2.x()/windowWidth, (windowHeight - v2.y())/windowHeight);
    //std::cout<<"PROBANDO COLISIONES: "<<xMin<<" <= "<<newV.x()<<" <= "<<xMax<<"?? y... "<<yMin<<" <= "<<newV.y()<<" <= "<<yMax<<" ??"<<std::endl;
    //std::cout<<"PROBANDO COLISIONES: "<<newV.x()<<" , "<<newV.y()<<") frente a: ("<<xMin<<" , "<< xMax <<") , ("<<yMin<<" , "<<yMax<<")"<<std::endl;
	//return (xMin <= newV.x() && yMin <= newV.y()) && (xMax >= newV.x() && yMax >= newV.y());
	return false;
}

void Box3D::init(Object* obj,int triangleIdx){
	this->obj=obj;
	this->triangleIdx = triangleIdx;
	update();
}

void Box3D::update(){
	
		std::vector<vertex_t>* vertexlist = ((Mesh*)obj->getComponent("mesh"))->vertexList;
		std::vector<int>* facelist = ((Mesh*)obj->getComponent("mesh"))->faceList;
		obj->transform->computeMatrix();
        
        Mat4 v2 = obj->transform->getMatrix(); // rectTransform
		Vec4 newpos;

        vertex_t v=vertexlist->data()[facelist->data()[triangleIdx *3]];    
        newpos = v2 * v.posicion;

        ver1 = Vec3(newpos.x(),newpos.y(),newpos.z());

		v = vertexlist->data()[facelist->data()[(triangleIdx * 3)+1]];
		newpos = v2 * v.posicion;

		ver2 = Vec3(newpos.x(), newpos.y(), newpos.z());

		v = vertexlist->data()[facelist->data()[(triangleIdx * 3) + 2]];
		newpos = v2 * v.posicion;

		ver3 = Vec3(newpos.x(), newpos.y(), newpos.z());

		Vec3 edge1 = ver2 - ver1;
		Vec3 edge2 = ver3 - ver1;
		Vec3 miniEdge1 = Vec3(edge1.x(), edge1.y(), edge1.z());
		Vec3 miniEdge2 = Vec3(edge2.x(), edge2.y(), edge2.z());
		Vec3 faceNormal = Utils::cross(miniEdge1, miniEdge2);
		Vec3 faceNormalized = Utils::normalize(faceNormal);
		Vec3 triPoint = (ver1 + ver2 + ver3) / 3.0f;

		//formula del plano: Ax + By + Cz + D = 0
		planeA = faceNormalized.x();
		planeB = faceNormalized.y();
		planeC = faceNormalized.z();
		planeD = -planeA * triPoint.x() - planeB * triPoint.y() - planeC * triPoint.z();
}

MeshCollider::MeshCollider(Object* obj)
{
    type = "collider";
	boxList=new std::vector<BV*>();
	int numtriangles=((Mesh*)obj->getComponent("mesh"))->faceList->size() / 3;
	//newbox->init(obj);
	for(int i=0;i<numtriangles;i++)
	{	
		BV* newbox;
		if(obj->getComponent("ui")) newbox = new Box2D();
		else newbox = new Box3D();
		newbox->init(obj, i);
		boxList->push_back(newbox);
	}	
}
	
void MeshCollider::update(){
	for(auto it= boxList->begin();it!= boxList->end();it++)
		(*it)->update();	
}

bool MeshCollider::collision(Collider* c2)
{
	if (c2 == nullptr) return false;
	if (instanceof<MeshCollider>(c2))
		return collisionMesh((MeshCollider*)c2);
	if (instanceof<BoxCollider>(c2))
		return collisionBox((BoxCollider*)c2);
	if (instanceof<SphereCollider>(c2))
		return collisionSphere((SphereCollider*)c2);
	return false;
}

bool MeshCollider::collisionMesh(MeshCollider* c2){
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

bool MeshCollider::collisionBox(BoxCollider* c2)
{
	auto it1 = boxList->begin();

	bool collision = false;
	while (!collision && it1 != boxList->end())
	{
		collision = c2->collisionTriangle((*it1));
		it1++;
	}
	return collision;
}

bool MeshCollider::collisionSphere(SphereCollider* c2)
{
	auto it1 = boxList->begin();

	bool collision = false;
	while (!collision && it1 != boxList->end())
	{
		collision = c2->collisionTriangle((*it1));
		it1++;
	}
	return collision;
}



bool MeshCollider::collisionPoint(Vec2 v2)
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
