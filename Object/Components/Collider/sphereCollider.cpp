#include "sphereCollider.h"

SphereCollider::SphereCollider(Camera* camera) {
    type = "collider";
    // gameObject->transform->computeMatrix();
    this->camera = camera;
}

bool SphereCollider::collision(Collider* c2)
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

Vec3 SphereCollider::getCenter()
{
    return center;
}

void SphereCollider::update()
{
    center = gameObject->transform->position + offset;
}

bool SphereCollider::collisionMesh(MeshCollider* c2)
{
    auto it1 = c2->boxList->begin();

    bool collision = false;
    while (!collision && it1 != c2->boxList->end())
    {
        //TODO
        it1++;
    }
    return collision;
}

bool SphereCollider::collisionSphere(SphereCollider* c2)
{
    float distance = std::sqrt(
        (center.x() - c2->center.x()) * (center.x() - c2->center.x()) +
        (center.y() - c2->center.y()) * (center.y() - c2->center.y()) +
        (center.z() - c2->center.z()) * (center.z() - c2->center.z())
    );
    return distance < radius + c2->radius;
}

bool SphereCollider::collisionBox(BoxCollider* c2)
{ 
    Vec3 pos = c2->getGameObject()->transform->position;
    Vec3 scale = c2->getGameObject()->transform->scale;
    float xMin = pos.x() + offset.x() * scale.x() - c2->bounds.x() / 2 * scale.x();
    float yMin = pos.y() + offset.y() * scale.y() - c2->bounds.y() / 2 * scale.y();
    float zMin = pos.z() + offset.z() * scale.z() - c2->bounds.z() / 2 * scale.z();
    float xMax = pos.x() + offset.x() * scale.x() + c2->bounds.x() / 2 * scale.x();
    float yMax = pos.y() + offset.y() * scale.y() + c2->bounds.y() / 2 * scale.y();
    float zMax = pos.z() + offset.z() * scale.z() + c2->bounds.z() / 2 * scale.z();

    float x = std::max(xMin, std::min(center.x(), xMax));
    float y = std::max(yMin, std::min(center.y(), yMax));
    float z = std::max(zMin, std::min(center.z(), zMax));

    // this is the same as isPointInsideSphere
    float distance = std::sqrt(
        (x - center.x()) * (x - center.x()) +
        (y - center.y()) * (y - center.y()) +
        (z - center.z()) * (z - center.z())
    );

    return distance < radius;
}

bool SphereCollider::collisionPoint(Vec2 v2) { return false; }