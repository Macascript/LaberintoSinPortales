#pragma once

#include "../Engine/Commons/common.h"
#include "Components/Transform/transform.h"
#include "component.h"
#include "../Engine/Input/input.h"
//#include "Components/Collider/collider.h"

class Component;

/**
Contenedor de Components y un Transform.
Es un objeto que se encuentra en el mundo de una escena.
*/
class Object {
private:
	/**
	Mapa de Components que posee el Object.
	La clave es el nombre en string del tipo del Component y el valor es un puntero a un Component.
	No puede haber más de un Component del mismo tipo.
	*/
	std::map<std::string,std::vector<Component*>*>* components = new std::map<std::string,std::vector<Component*>*>();
	/**
	Contador de Objects para ir asignando ids a cada uno.
	*/
	static int idCounter;
	/**
	Id del Object que se usará para recuperarlo del mapa de Objects.
	*/
	int id = 0;

public:
	/**
	Puntero al Transform asociado a este Object.
	Es obligatorio tener uno, se crea con el Object y se destruye con el Object.
	*/
	Transform* transform;

	/**
	Flag para destruir este Object en el siguiente frame.
	Los objetos no se deben destruir manualmente, para destruirlos solo se pone a true esta variable.
	*/
	bool markedDelete = false;

	/**
	Constructor por defecto.
	Crea el Object con su Transform
	*/
	Object();

	/**
	[En Desuso]
	*/
	Object(std::string fileName);

	/**
	Devuelve el id del Object que se usará para recuperarlo del mapa de Objects.
	*/
	int getId();
	
	/**
	Método llamado cada frame. LLama al update de todos sus componentes.
	*/
	virtual void update();

	/**
	Si tiene un componente del tipo type lo devuelve, sino devuelve nullptr
	*/
	Component* getComponent(std::string type, int index = 0);

	/**
	Añade el componente que se pasa por parámetro.
	Si ya contaba con un componente del mismo tipo, imprime error y no hace nada.
	*/
	void addComponent(Component* component);

	/**
	Elimina el componente del tipo type.
	Si no tiene un componente de ese tipo, imprime error y no hace nada.
	*/
	void removeComponent(std::string type);

	/**
	Destructor de Object.
	Destruye con él a todos sus componentes y a su Transform.
	*/
	~Object();
};