#pragma once
#include "../../../Engine/Commons/common.h"
#include "../../../Engine/Datatypes/Utils/utils.h"
#include "../../../Engine/Input/input.h"
#include "../Collider/boxCollider.h"

class Object;
class BoxCollider;

typedef enum cameraType_e {
	perspective,
	ortho
}cameraType_e;

class Camera:public Object{

public:
	Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 position;
	Vec3 rotation;
	Vec3 lookAt;
	Mat4 viewMatrix;
	Mat4 projMatrix;
	cameraType_e type = perspective;
	double horizontalAngle = 3.14f;
	double verticalAngle = 0;

	float alphaDegrees = 90;
	float fovy = Utils::radians(alphaDegrees);
	float aspect = 4.0f / 3.0f;
	float zNear = 0.01f;
	float zFar = 100.0f;

	Camera(Vec3 pos, Vec3 lookAt, cameraType_e type);

	void step();
	void computeMatrix();
	Mat4& getMatrix();
	Mat4& getProjectionMatrix();

	void setLookAt(Vec3 newLookAt);
	void setPosition(Vec3 newPosition);
};
