#pragma once
#define NOMBRE_ARCHIVO "map.lsp"
#define CELLDISTANCE 20
#define COLUMNSLAB 18 
#include "../../Object/Components/UI/ui.h"
#include "../../Object/Components/Collider/boxCollider.h"
#include "../../Scene/scene.h"
#include "../../Object/Components/Text/text.h"

class LaberintoScene : public Scene {
private:
	std::map<int,Object*>* laberinto = new std::map<int,Object*>();
public:
	LaberintoScene(Camera* camera) : Scene(camera) {}
	void init() override;
	void userUpdate() override;
	void createCelda(std::string modelo, int x, int z, int angulo, bool primera, bool segunda, bool tercera, bool cuarta);
	void genLaberinto();
	~LaberintoScene();
};