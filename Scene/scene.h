#pragma once
#include "../Object/Components/Camera/camera.h"
#include "../Object/Components/Mesh/mesh.h"
#include "../Object/Components/Text/text.h"
#include "../Object/Components/Button/button.h"
#define USER_PATH ".\\User\\"
#define windowWidth 640
#define windowHeight 480

class Scene {
private:
	// static Scene* scene = nullptr;

	void addObject(Object* obj);
	void removeObject(Object* obj);

protected:
	Camera* camera = nullptr;
	void createObject(Object* obj);

public:
	std::map<int, Object*>* objectList;
	std::map<int, Object*>* addedObjectList;
	Scene(Camera* cam);
	virtual void init() {};
	Camera* getCamera();
	void setCamera(Camera* camera);
	void update();
};