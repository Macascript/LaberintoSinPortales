#pragma once

#include "../../Object/Components/UI/ui.h" 
#include "../../Scene/scene.h"
#include "../../Object/Components/Text/text.h"

class MenuScene: public Scene{
public:
	MenuScene(Camera* camera): Scene(camera){}
	void init() override;
	void userUpdate() override;
};