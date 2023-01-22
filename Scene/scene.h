#pragma once
#include "../Object/Components/Camera/camera.h"
#include "../Object/Components/Mesh/mesh.h"
//#include "../Object/Components/Text/text.h"
#include "../Object/Components/Button/button.h"
#include "../User/SceneManager/scenemanager.h"
#include "../Object/Light/light.h"
#include "spatialHashing.h"
#define USER_PATH ".\\User\\"

class SceneManager;
class Camera;
class Light;
class SpatialHashing;

class Scene {
private:
	// static Scene* scene = nullptr;

	void addObject(Object* obj);
	void removeObject(Object* obj);
	std::vector<Light*>* lightList;
	SpatialHashing* sceneGrid = nullptr;

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
	std::vector<Object*>* getCollisions(Object* obj);
	std::vector<Object*>* getCollisions(Collider* col);
};