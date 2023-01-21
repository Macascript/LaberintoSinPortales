#pragma once

#include "../Object/object.h"

class Object;

class SpatialHashing {

public:

	std::map<int, Object*>* objList = nullptr;
	int numFilas;
	int numColumnas;
	int numCeldas;
	float tamX, tamY, tamZ;
	float minX, minY, minZ;
	std::map<int, Object*>*** grid;

	SpatialHashing(std::map<int, Object*>* objList, int numFilas, int numColumnas, int numCeldas, float minX, float minY, float minZ, float tamX, float tamY, float tamZ);

	void update();

};