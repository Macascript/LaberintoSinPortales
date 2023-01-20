#pragma once
#include "../Object/Components/Camera/camera.h"
#include "../Object/Components/Mesh/mesh.h"
#include "../Object/Components/Text/text.h"
#include "../Object/Components/Button/button.h"
#include "../User/SceneManager/scenemanager.h"
#include "../Object/Light/light.h"
#define USER_PATH ".\\User\\"
#define windowWidth 960
#define windowHeight 720

class SceneManager;

class Scene {
private:
	// static Scene* scene = nullptr;

	void addObject(Object* obj);
	void removeObject(Object* obj);
	std::vector<Light*>* lightList;

protected:
	Camera* camera = nullptr;
	void createObject(Object* obj);

public:
	std::map<int, Object*>* objectList;
	std::map<int, Object*>* addedObjectList;
	Scene(Camera* cam);
	virtual void init() {};
	virtual void userUpdate() {};
	Camera* getCamera();
	void setCamera(Camera* camera);
	void update();
	std::vector<Light*>* getLights();
	void addLight(Light* light);
};