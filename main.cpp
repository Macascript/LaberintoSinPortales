

#include "Engine/Window/window.h"
#include "Engine/Input/input.h"
#include "Engine/Render/render.h"
#include "Scene/scene.h"
#include "User/SceneManager/scenemanager.h"

int main(){

    Window* window = new Window(windowWidth, windowHeight, "Prueba 1 GLFW");

    Input* input = Input::getInput();
	input->init(window);

    Render* render = new Render();

	Camera* camera = new Camera(Vec3(0.0f, 0.0f, -18.0f), Vec3(0.0f, 0.0f, -17.999f),perspective);
	SceneManager* sceneManager = new SceneManager(camera);
	// sceneManager->initSceneList();
	
	sceneManager->actualScene()->init();
	//delete sceneManager;
	//std::cout << "patata7" << std::endl;
	sceneManager->actualScene()->setCamera(camera);
	//std::cout << "patata8" << std::endl;

    while (window->stillAlive())
	{
		if (window->renderfps(60.0f)) {
			render->drawScene(sceneManager->actualScene());
			sceneManager->actualScene()->update();//0.0
			window->update();
		}
	}

	delete sceneManager;
	delete render;
	delete window;
	delete camera;
    return 0;
}