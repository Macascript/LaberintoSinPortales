#include "camera.h"

Camera::Camera(Vec3 pos, Vec3 lookAt, cameraType_e type) {
	this->position = pos;

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

void Camera::step()
{
	Vec3 auxVector = lookAt - position;
	auxVector.getY() = 0;
	Vec3 auxCross = Utils::cross(auxVector, up);
	Vec3 auxCrossRight = Utils::cross(auxVector, up);

	if (Input::getKey('W')) {
		position = position + Utils::normalize(auxVector) * Input::getSpeed();
		lookAt = lookAt + Utils::normalize(auxVector) * Input::getSpeed();
	}

	if (Input::getKey('S')) {
		position = position - Utils::normalize(auxVector) * Input::getSpeed();
		lookAt = lookAt - Utils::normalize(auxVector) * Input::getSpeed();
	}

	if (Input::getKey('D'))
	{
		position = position + Utils::normalize(auxCross) * Input::getSpeed();
		lookAt = lookAt + Utils::normalize(auxCross) * Input::getSpeed();
	}

	if (Input::getKey('A'))
	{
		position = position - Utils::normalize(auxCross) * Input::getSpeed();
		lookAt = lookAt - Utils::normalize(auxCross) * Input::getSpeed();
	}

	if (Input::getKey('M')) {
		lookAt.getX() = cos(-7.283f / 360) * (lookAt.x() - position.x()) + sin(-7.283f / 360) * (lookAt.z() - position.z()) + position.x();
		lookAt.getZ() = -sin(-7.283f / 360) * (lookAt.x() - position.x()) + cos(-7.283f / 360) * (lookAt.z() - position.z()) + position.z();
	}

	if (Input::getKey('N')) {
		lookAt.getX() = cos(7.283f / 360) * (lookAt.x() - position.x()) + sin(7.283f / 360) * (lookAt.z() - position.z()) + position.x();
		lookAt.getZ() = -sin(7.283f / 360) * (lookAt.x() - position.x()) + cos(7.283f / 360) * (lookAt.z() - position.z()) + position.z();
	}

	horizontalAngle = Input::getMouseSpeed() * Input::getDeltaTime() * (Input::getMousePosition().x() - float((960 / 2)));
	verticalAngle = Input::getMouseSpeed() * Input::getDeltaTime() * (Input::getMousePosition().y() - float((720 / 2)));

	lookAt.getX() = cos(-horizontalAngle / 360) * (lookAt.x() - position.x()) + sin(-horizontalAngle / 360) * (lookAt.z() - position.z()) + position.x();
	lookAt.getY() = cos(-verticalAngle / 360) * (lookAt.y() - position.y()) + sin(-verticalAngle / 360) * (abs(lookAt.z() - position.z())) + sin(-verticalAngle / 360) * (abs(lookAt.x() - position.x())) + position.y();
	lookAt.getZ() = -sin(-horizontalAngle / 360) * (lookAt.x() - position.x()) + cos(-horizontalAngle / 360) * (lookAt.z() - position.z()) + position.z();

	//up = Utils::cross(right, lookAt);
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