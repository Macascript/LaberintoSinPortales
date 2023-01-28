# include "boxCollider.h"

BoxCollider::BoxCollider(Camera* camera){
    type = "collider";
    // gameObject->transform->computeMatrix();
    this->camera = camera;
}

// void BoxCollider::init(){

// }

void BoxCollider::update()
{

}

bool BoxCollider::collision(Collider* c2)
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

bool BoxCollider::collisionBox(BoxCollider* c2)
{
    Vec3 pos = gameObject->transform->position;
    Vec3 scale = gameObject->transform->scale;
    float xMin = pos.x() + offset.x() * scale.x() - bounds.x() / 2 * scale.x();
    float yMin = pos.y() + offset.y() * scale.y() - bounds.y() / 2 * scale.y();
    float zMin = pos.z() + offset.z() * scale.z() - bounds.z() / 2 * scale.z();
    float xMax = pos.x() + offset.x() * scale.x() + bounds.x() / 2 * scale.x();
    float yMax = pos.y() + offset.y() * scale.y() + bounds.y() / 2 * scale.y();
    float zMax = pos.z() + offset.z() * scale.z() + bounds.z() / 2 * scale.z();

    Vec3 posC2 = c2->gameObject->transform->position;
    Vec3 scaleC2 = c2->gameObject->transform->scale;

    float xMinC2 = posC2.x() + c2->offset.x() * scaleC2.x() - c2->bounds.x() / 2 * scaleC2.x();
    float yMinC2 = posC2.y() + c2->offset.y() * scaleC2.y() - c2->bounds.y() / 2 * scaleC2.y();
    float zMinC2 = posC2.z() + c2->offset.z() * scaleC2.z() - c2->bounds.z() / 2 * scaleC2.z();
    float xMaxC2 = posC2.x() + c2->offset.x() * scaleC2.x() + c2->bounds.x() / 2 * scaleC2.x();
    float yMaxC2 = posC2.y() + c2->offset.y() * scaleC2.y() + c2->bounds.y() / 2 * scaleC2.y();
    float zMaxC2 = posC2.z() + c2->offset.z() * scaleC2.z() + c2->bounds.z() / 2 * scaleC2.z();

    /*if((xMin<xMaxC2 && xMin>xMinC2)&&(yMin<yMaxC2 && yMin>yMinC2)&&(zMin<zMaxC2 && zMin>zMinC2)) return true;
    if((xMin<xMaxC2 && xMin>xMinC2)&&(yMax<yMaxC2 && yMax>yMinC2)&&(zMax<zMaxC2 && zMax>zMinC2)) return true;
    if((xMax<xMaxC2 && xMax>xMinC2)&&(yMin<yMaxC2 && yMin>yMinC2)&&(zMin<zMaxC2 && zMin>zMinC2)) return true;
    if((xMax<xMaxC2 && xMax>xMinC2)&&(yMax<yMaxC2 && yMax>yMinC2)&&(zMax<zMaxC2 && zMax>zMinC2)) return true;

    if((xMin<xMaxC2 && xMin>xMinC2)&&(yMin<yMaxC2 && yMin>yMinC2)&&(zMax<zMaxC2 && zMax>zMinC2)) return true;
    if((xMin<xMaxC2 && xMin>xMinC2)&&(yMax<yMaxC2 && yMax>yMinC2)&&(zMin<zMaxC2 && zMin>zMinC2)) return true;
    if((xMax<xMaxC2 && xMax>xMinC2)&&(yMin<yMaxC2 && yMin>yMinC2)&&(zMax<zMaxC2 && zMax>zMinC2)) return true;
    if((xMax<xMaxC2 && xMax>xMinC2)&&(yMax<yMaxC2 && yMax>yMinC2)&&(zMin<zMaxC2 && zMin>zMinC2)) return true;*/
    //std::cout << "Objeto: " << "( " << xMin << ", " << yMin << ", " << zMin << " )" << "( " << xMax << ", " << yMax << ", " << zMax << " )" << std::endl;
    //std::cout << "Camara: " << "( " << c2->xMin << ", " << c2->yMin << ", " << c2->zMin << " )" << "( " << c2->xMax << ", " << c2->yMax << ", " << c2->zMax << " )" << std::endl;
    
    if ((xMin<xMaxC2 && xMax>xMinC2) && (yMin<yMaxC2 && yMax>yMinC2) && (zMin<zMaxC2 && zMax>zMinC2)) return true;

	return false;
}

bool BoxCollider::collisionMesh(MeshCollider* c2)
{
    auto it1 = c2->boxList->begin();

    bool collision = false;
    while (!collision && it1 != c2->boxList->end())
    {
        collision = this->collisionTriangle((*it1));
        it1++;
    }
    return collision;
}

bool BoxCollider::collisionTriangle(BV* _b2)
{
    Box3D* b2 = (Box3D*)_b2;

    return false;
}

bool BoxCollider::collisionSphere(SphereCollider* c2)
{ 
    Vec3 pos = gameObject->transform->position;
    Vec3 scale = gameObject->transform->scale;
    float xMin = pos.x() + offset.x() * scale.x() - bounds.x() / 2 * scale.x();
    float yMin = pos.y() + offset.y() * scale.y() - bounds.y() / 2 * scale.y();
    float zMin = pos.z() + offset.z() * scale.z() - bounds.z() / 2 * scale.z();
    float xMax = pos.x() + offset.x() * scale.x() + bounds.x() / 2 * scale.x();
    float yMax = pos.y() + offset.y() * scale.y() + bounds.y() / 2 * scale.y();
    float zMax = pos.z() + offset.z() * scale.z() + bounds.z() / 2 * scale.z();

    float x = std::max(xMin, std::min(c2->getCenter().x(), xMax));
    float y = std::max(yMin, std::min(c2->getCenter().y(), yMax));
    float z = std::max(zMin, std::min(c2->getCenter().z(), zMax));

    // this is the same as isPointInsideSphere
    float distance = std::sqrt(
        (x - c2->getCenter().x()) * (x - c2->getCenter().x()) +
        (y - c2->getCenter().y()) * (y - c2->getCenter().y()) +
        (z - c2->getCenter().z()) * (z - c2->getCenter().z())
    );

    return distance < c2->radius;
}

bool BoxCollider::collisionPoint(Vec2 v2){
    Vec3 pos = gameObject->transform->position;
    Mat4 m = gameObject->transform->getMatrix();
    Mat4 proj = camera->getProjectionMatrix();
    Mat4 view = camera->viewMatrix;
    Vec4 _000 = proj * view * m * Vec4(pos + offset - bounds/2,1.0f); // (0, 0, 0)
    Vec4 _001 = proj * view * m * Vec4(pos + offset + Vec3(-bounds.x()/2,-bounds.y()/2,bounds.z()/2),1.0f); // (0, 0, 1)
    Vec4 _010 = proj * view * m * Vec4(pos + offset + Vec3(-bounds.x()/2,bounds.y()/2,-bounds.z()/2), 1.0f); // (0, 1, 0)
    Vec4 _011 = proj * view * m * Vec4(pos + offset + Vec3(-bounds.x()/2,bounds.y()/2,bounds.z()/2), 1.0f); // (0, 1, 1)
    Vec4 _100 = proj * view * m * Vec4(pos + offset + Vec3(bounds.x()/2,-bounds.y()/2,-bounds.z()/2), 1.0f); // (1, 0, 0)
    Vec4 _101 = proj * view * m * Vec4(pos + offset + Vec3(bounds.x()/2,-bounds.y()/2,bounds.z()/2), 1.0f); // (1, 0, 1)
    Vec4 _110 = proj * view * m * Vec4(pos + offset + Vec3(bounds.x()/2,bounds.y()/2,-bounds.z()/2), 1.0f); // (1, 1, 0)
    Vec4 _111 = proj * view * m * Vec4(pos + offset + bounds/2, 1.0f); // (1, 1, 1)
    float xMin = _000.x();
    float yMin = _000.y();
    float xMax = _000.x();
    float yMax = _000.y();
    if (_001.x() < xMin) xMin = _001.x();
    if (_010.x() < xMin) xMin = _010.x();
    if (_011.x() < xMin) xMin = _011.x();
    if (_100.x() < xMin) xMin = _100.x();
    if (_101.x() < xMin) xMin = _101.x();
    if (_110.x() < xMin) xMin = _110.x();
    if (_111.x() < xMin) xMin = _111.x();

    if (_001.x() > xMax) xMax = _001.x();
    if (_010.x() > xMax) xMax = _010.x();
    if (_011.x() > xMax) xMax = _011.x();
    if (_100.x() > xMax) xMax = _100.x();
    if (_101.x() > xMax) xMax = _101.x();
    if (_110.x() > xMax) xMax = _110.x();
    if (_111.x() > xMax) xMax = _111.x();

    if (_001.x() < yMin) yMin = _001.y();
    if (_010.x() < yMin) yMin = _010.y();
    if (_011.x() < yMin) yMin = _011.y();
    if (_100.x() < yMin) yMin = _100.y();
    if (_101.x() < yMin) yMin = _101.y();
    if (_110.x() < yMin) yMin = _110.y();
    if (_111.x() < yMin) yMin = _111.y();

    if (_001.x() > yMax) yMax = _001.y();
    if (_010.x() > yMax) yMax = _010.y();
    if (_011.x() > yMax) yMax = _011.y();
    if (_100.x() > yMax) yMax = _100.y();
    if (_101.x() > yMax) yMax = _101.y();
    if (_110.x() > yMax) yMax = _110.y();
    if (_111.x() > yMax) yMax = _111.y();

    Vec2 newV = Vec2(v2.x()/windowWidth, (windowHeight - v2.y())/windowHeight);
	return (xMin <= newV.x() && yMin <= newV.y()) && (xMax >= newV.x() && yMax >= newV.y());
}