#include "LookAtFollower.h"

LookAtFollower::LookAtFollower(Camera* cam) {
	this->cam = cam;
}

void LookAtFollower::update() {
	gameObject->transform->position.getX() = cam->lookAt.x();
	gameObject->transform->position.getY() = cam->lookAt.y();
	gameObject->transform->position.getZ() = cam->lookAt.z();
}