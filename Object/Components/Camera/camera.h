#pragma once
#include "../../../Engine/Commons/common.h"
#include "../../../Engine/Datatypes/Utils/utils.h"

typedef enum cameraType_e {
	perspective,
	ortho
}cameraType_e;

class Camera{

public:
	Vec3 up;
	Vec3 position;
	Vec3 rotation;
	Vec3 lookAt;
	Mat4 viewMatrix;
	Mat4 projMatrix;
	cameraType_e type = perspective;

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
};
