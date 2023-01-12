#pragma once

#include "../../Object/Components/UI/ui.h" 

class MenuScene: public Scene{
public:
	MenuScene(Camera* camera): Scene(camera){}
	void init() override;
};