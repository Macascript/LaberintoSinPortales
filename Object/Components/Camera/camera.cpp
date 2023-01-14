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
	Vec3 auxCross = Utils::cross(auxVector, up);

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

	horizontalAngle = Input::getMouseSpeed() * Input::getDeltaTime() * float((960 / 2) - Input::getMousePosition().x());
	verticalAngle = Input::getMouseSpeed() * Input::getDeltaTime() * float((720 / 2) - Input::getMousePosition().y());

	/*lookAt = Vec3(
		cos(Utils::radians(horizontalAngle)) * (lookAt.x() - position.x()) + sin(Utils::radians(horizontalAngle)) * (lookAt.z() - position.z()) + position.x(),
		lookAt.y(),
		-sin(Utils::radians(horizontalAngle)) * (lookAt.x() - position.x()) + cos(Utils::radians(horizontalAngle)) * (lookAt.z() - position.z()) + position.z()
	);*/

	//std::cout << horizontalAngle << "º, " << verticalAngle << "º" <<std::endl;

	/*lookAt = Vec3(
		cos(Utils::radians(verticalAngle)) * sin(Utils::radians(horizontalAngle)),
		sin(Utils::radians(verticalAngle)),
		cos(Utils::radians(verticalAngle)) * cos(Utils::radians(horizontalAngle))
	);*/

	/*Vec3 right = Vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	up = Utils::cross(right, lookAt);*/
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