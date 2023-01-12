#include "camera.h"

Camera::Camera(Vec3 pos, Vec3 lookAt, cameraType_e type) {
	//std::cout << "patata1" << std::endl;
	this->position = pos;

	//std::cout << "patata2" << std::endl;
	this->lookAt = lookAt;

	//std::cout << "patata3" << std::endl;
	this->rotation = Vec3(0.0f, 0.0f, 0.0f);

	//std::cout << "patata4" << std::endl;
	this->viewMatrix = Mat4(1.0f);

	//std::cout << "patata5" << std::endl;
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

void Camera::step() {


	/*if (InputManager::keys['W'])
	{
		rotation.z += 0.01f;

		lookAt.y += 0.01f;
		lookAt.z += 0.01f;
	}

	if (InputManager::keys['S'])
	{
		rotation.z -= 0.01f;

		lookAt.y -= 0.01f;
		lookAt.z -= 0.01f;
	}*/
}

void Camera::computeMatrix() {
	//std::cout << "patata10" << std::endl;
	Vec3 aux = Vec3(0, 1.0f, 0);
	this->viewMatrix = Utils::lookAt(position, lookAt, aux);
	//std::cout << "patata11" << std::endl;
}

Mat4& Camera::getMatrix() {

	return this->viewMatrix;
}

Mat4& Camera::getProjectionMatrix() {
	
	return this->projMatrix;
}