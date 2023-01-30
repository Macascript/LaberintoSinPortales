#pragma once
#include "../engine.h"

class PortalScene : public Scene {
public:
	PortalScene(Camera* camera) : Scene(camera) {}
	void init() override;
	void userUpdate() override;
	// ~PortalScene();
};