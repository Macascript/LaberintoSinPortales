#include "transform.h"

Transform::Transform(bool isCanvas){
    this->position = Vec3(0.0f, 0.0f, 0.0f);
    this->isCanvas = isCanvas;
}

Mat4 Transform::getMatrix()
{
	return this->modelMatrix;
}

void Transform::computeMatrix()
{
	Mat4 aux1 = Mat4(1.0f);
	Mat4 matT = Utils::translate(aux1, this->position);

	Vec3 aux2 = Vec3(1.0f, 0, 0);
	matT = Utils::rotate(matT, this->rotation.x(), aux2);

	aux2 = Vec3(0, 1.0f, 0);
	matT = Utils::rotate(matT, this->rotation.y(), aux2);

	aux2 = Vec3(0, 0, 1.0f);
	matT = Utils::rotate(matT, this->rotation.z(), aux2);
	matT = Utils::scale(matT, this->scale);

	this->modelMatrix = matT;
}