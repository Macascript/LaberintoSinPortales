#include "spatialHashing.h"

SpatialHashing::SpatialHashing(std::map<int, Object*>* objList,
	int numFilas, int numColumnas, int numCeldas,
	float minX, float minY, float minZ,
	float tamX, float tamY, float tamZ)
{

	this->objList = objList;
	this->numFilas = numFilas;
	this->numColumnas = numColumnas;
	this->numCeldas = numCeldas;
	this->minX = minX;
	this->minY = minY;
	this->minZ = minZ;
	this->tamX = tamX;
	this->tamY = tamY;
	this->tamZ = tamZ;


	grid = new std::map<int, Object*>**[numFilas];

	for (int i = 0; i < numFilas; i++) {

		grid[i] = new std::map<int, Object*>*[numColumnas];

		for (int j = 0; j < numColumnas; j++) {

			grid[i][j] = new std::map<int, Object*>[numCeldas];
		}
	}

	update();
}


void SpatialHashing::update() {

	for (int i = 0; i < numFilas; i++) {
		for (int j = 0; j < numColumnas; j++) {
			for (int z = 0; z < numCeldas; z++)
			{
				grid[i][j][z].clear();
			}
		}
	}

	for (auto obj = objList->begin(); obj != objList->end(); obj++)
	{
		int key = obj->first;
		Object* object = obj->second;

		int coordX = (object->transform->position.x() - minX) / (tamX / numColumnas);
		int coordY = (object->transform->position.y() - minY) / (tamY / numFilas);
		int coordZ = (object->transform->position.z() - minZ) / (tamZ / numCeldas);

		if (((coordX >= 0) && coordX < numColumnas) &&
			((coordY >= 0) && coordY < numFilas) &&
			((coordZ >= 0) && coordZ < numCeldas))
		{

			grid[coordY][coordX][coordZ][key] = object;
		}

	}

}