#include "camera.h"

Camera::Camera(Vec3 pos, Vec3 lookAt, cameraType_e type) {
	this->position = pos;
	transform->position = pos;

	this->lookAt = lookAt;

	this->rotation = Vec3(0.0f, 0.0f, 0.0f);

	this->viewMatrix = Mat4(1.0f);

	this->type = type;
	switch (type) {

	case perspective:
		projMatrix = Utils::perspective(fovy, aspect, zNear, zFar);
		break;

	case ortho:
		projMatrix = Utils::ortho(0.0f, 640, 0.0f, 480, zNear, zFar);
		break;

	default:
		break;
	};
	//std::cout << "patata6" << std::endl;
}

void Camera::update()
{
	Object::update();
	// this->transform->position = position;
	Vec3 actualLookAt = lookAt;
	Vec3 auxVector = lookAt - this->transform->position;
	auxVector.getY() = 0;
	Vec3 auxCross = Utils::cross(auxVector, up);
	//Vec3 auxCrossRight = Utils::cross(auxVector, up);

	if (Input::getKey('W')) {
		this->transform->position = this->transform->position + Utils::normalize(auxVector) * Input::getSpeed();
		lookAt = lookAt + Utils::normalize(auxVector) * Input::getSpeed();

		Vec3 futureTransform = transform->position;
		transform->position.getZ() = position.z();
		bool canX = SceneManager::actualScene()->getCollisions(this)->size() == 0;
		transform->position.getZ() = futureTransform.z();
		transform->position.getX() = position.x();
		bool canZ = SceneManager::actualScene()->getCollisions(this)->size() == 0;
		if (canX){
			transform->position.getX() = futureTransform.x();
		}
		if (!canZ){
			transform->position.getZ() = position.z();
		}
		position = transform->position;
	}

	if (Input::getKey('S')) {
		this->transform->position = this->transform->position - Utils::normalize(auxVector) * Input::getSpeed();
		lookAt = lookAt - Utils::normalize(auxVector) * Input::getSpeed();

		Vec3 futureTransform = transform->position;
		transform->position.getZ() = position.z();
		bool canX = SceneManager::actualScene()->getCollisions(this)->size() == 0;
		transform->position.getZ() = futureTransform.z();
		transform->position.getX() = position.x();
		bool canZ = SceneManager::actualScene()->getCollisions(this)->size() == 0;
		if (canX){
			transform->position.getX() = futureTransform.x();
		}
		if (!canZ){
			transform->position.getZ() = position.z();
		}
		position = transform->position;
	}

	if (Input::getKey('D'))
	{
		this->transform->position = this->transform->position + Utils::normalize(auxCross) * Input::getSpeed();
		lookAt = lookAt + Utils::normalize(auxCross) * Input::getSpeed();

		if (SceneManager::actualScene()->getCollisions(this)->size() == 0)
		{
			position = transform->position;
		}
			
		else
		{
			transform->position = position;
			lookAt = actualLookAt;
		}
	}

	if (Input::getKey('A'))
	{
		this->transform->position = this->transform->position - Utils::normalize(auxCross) * Input::getSpeed();
		lookAt = lookAt - Utils::normalize(auxCross) * Input::getSpeed();

		if (SceneManager::actualScene()->getCollisions(this)->size() == 0)
		{
			position = transform->position;
		}
			
		else
		{
			transform->position = position;
			lookAt = actualLookAt;
		}
	}

	if (Input::getKey('M')) {
		lookAt.getX() = cos(-7.283f / 360) * (lookAt.x() - this->transform->position.x()) + sin(-7.283f / 360) * (lookAt.z() - this->transform->position.z()) + this->transform->position.x();
		lookAt.getZ() = -sin(-7.283f / 360) * (lookAt.x() - this->transform->position.x()) + cos(-7.283f / 360) * (lookAt.z() - this->transform->position.z()) + this->transform->position.z();
	}

	if (Input::getKey('N')) {
		lookAt.getX() = cos(7.283f / 360) * (lookAt.x() - this->transform->position.x()) + sin(7.283f / 360) * (lookAt.z() - this->transform->position.z()) + this->transform->position.x();
		lookAt.getZ() = -sin(7.283f / 360) * (lookAt.x() - this->transform->position.x()) + cos(7.283f / 360) * (lookAt.z() - this->transform->position.z()) + this->transform->position.z();
	}

	horizontalAngle = Input::getMouseSpeed() * Input::getDeltaTime() * (Input::getMousePosition().x() - float((windowWidth / 2)));
	verticalAngle = Input::getMouseSpeed() * Input::getDeltaTime() * (Input::getMousePosition().y() - float((windowHeight / 2)));

	//  lookAt.getX() = cos(-horizontalAngle / 360) * (lookAt.x() - position.x()) + sin(-horizontalAngle / 360) * (lookAt.z() - position.z())/* + sin(-horizontalAngle / 360) * (lookAt.y() - position.y()) */ + position.x();
	//  lookAt.getY() = cos(-verticalAngle / 360) * (lookAt.y() - position.y()) + sin(-verticalAngle / 360) * (abs(lookAt.z() - position.z())) + sin(-verticalAngle / 360) * (abs(lookAt.x() - position.x())) + position.y();
	//  lookAt.getZ() = -sin(-horizontalAngle / 360) * (lookAt.x() - position.x()) + cos(-horizontalAngle / 360) * (lookAt.z() - position.z())/* - sin(-horizontalAngle / 360) * (lookAt.y() - position.y())*/ + position.z();

	// postolook = aux;
	// v = Utils::cross(postolook, v);
	// lookAt = position + (postolook * cos(verticalAngle / 360) + Utils::cross(v, postolook) * sin(verticalAngle / 360) + v * (v * postolook) * (1 - cos(verticalAngle / 360)));
	
	//up = Utils::cross(right, lookAt);
	// Vec3 futureTransform = transform->position;
	// transform->position.getZ() = position.z();
	// bool canX = SceneManager::actualScene()->getCollisions(this)->size() == 0;
	// transform->position.getZ() = futureTransform.z();
	// transform->position.getX() = position.x();
	// bool canZ = SceneManager::actualScene()->getCollisions(this)->size() == 0;
	// if (canX){
	// 	transform->position.getX() = futureTransform.x();
	// }
	// if (!canZ){
	// 	transform->position.getZ() = position.z();
	// }
	// position = transform->position;
	// if (SceneManager::actualScene()->getCollisions(this)->size() == 0)
	// {
	// 	position = transform->position;
	// }
		
	// else
	// {
	// 	transform->position = position;
	// 	lookAt = actualLookAt;
	// }

	Vec3 v = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 postolook = lookAt - this->transform->position;
	Vec3 aux = postolook * cos(-horizontalAngle / 360) + Utils::cross(v, postolook) * sin(-horizontalAngle / 360) + v * (v * postolook) * (1 - cos(-horizontalAngle / 360));
	lookAt = this->transform->position + aux;
	lookAt.getY() = cos(-verticalAngle / 360) * (lookAt.y() - this->transform->position.y()) + sin(-verticalAngle / 360) * (abs(lookAt.z() - this->transform->position.z())) + sin(-verticalAngle / 360) * (abs(lookAt.x() - this->transform->position.x())) + this->transform->position.y();
}

void Camera::computeMatrix()
{
	Vec3 aux = Vec3(0, 1.0f, 0);
	this->viewMatrix = Utils::lookAt(position, lookAt, aux);
}

Mat4& Camera::getMatrix()
{
	return this->viewMatrix;
}

Mat4& Camera::getProjectionMatrix()
{
	return this->projMatrix;
}