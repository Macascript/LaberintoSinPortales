#include "sphereCollider.h"

SphereCollider::SphereCollider(Camera* camera) {
    type = "collider";
    // gameObject->transform->computeMatrix();
    this->camera = camera;
}

bool SphereCollider::collision(Collider* c2)
{
    center = gameObject->transform->position + offset;
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
        collision = this->collisionTriangle(*it1);
        it1++;
    }
    return collision;
}

bool SphereCollider::collisionTriangle(BV* _b2)
{
    Box3D* b2 = (Box3D*)_b2;

    Vec3 A = b2->ver1 - center;
    Vec3 B = b2->ver2 - center;
    Vec3 C = b2->ver3 - center;
    Vec3 edge1 = B - A;
    Vec3 edge2 = C - A;
    Vec3 edge2bis = A - C;
    Vec3 edge3 = C - B;
    float rr = radius * radius;
    Vec3 V = Utils::cross(edge1, edge2);
    float d = Utils::dot(A, V);
    float e = Utils::dot(V, V);
    bool sep1 = d * d > rr * e;
    float aa = Utils::dot(A, A);
    float ab = Utils::dot(A, B);
    float ac = Utils::dot(A, C);
    float bb = Utils::dot(B, B);
    float bc = Utils::dot(B, C);
    float cc = Utils::dot(C, C);
    bool sep2 = (aa > rr) && (ab > aa) && (ac > aa);
    bool sep3 = (bb > rr) && (ab > bb) && (bc > bb);
    bool sep4 = (cc > rr) && (ac > cc) && (bc > cc);
    //AB = B - A
    //BC = C - B
    //CA = A - C
    float d1 = ab - aa;
    float d2 = bc - bb;
    float d3 = ac - cc;
    float e1 = Utils::dot(edge1, edge1);
    float e2 = Utils::dot(edge3, edge3);
    float e3 = Utils::dot(edge2bis, edge2bis);
    Vec3 Q1 = A * e1 - (edge1 * d1);
    Vec3 Q2 = B * e2 - (edge3 * d2);
    Vec3 Q3 = C * e3 - (edge2bis * d3);
    Vec3 QC = C * e1 - Q1;
    Vec3 QA = A * e2 - Q2;
    Vec3 QB = B * e3 - Q3;
    bool sep5 = (Utils::dot(Q1, Q1) > rr * e1 * e1) && (Utils::dot(Q1, QC) > 0);
    bool sep6 = (Utils::dot(Q2, Q2) > rr * e2 * e2) && (Utils::dot(Q2, QA) > 0);
    bool sep7 = (Utils::dot(Q3, Q3) > rr * e3 * e3) && (Utils::dot(Q3, QB) > 0);
    bool separated = sep1 || sep2 || sep3 || sep4 || sep5 || sep6 || sep7;
    return !separated;
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