#pragma once
class Component;

//#include "../Engine/Commons/common.h"
#include "../Object/object.h"

class Object;
class UI;

/**
	Clase padre de todos los componentes.
	No crear instancias de esta clase.
	Hereda de esta clase para crear un nuevo componente.
	Implementa el patr�n Components: toda funcionalidad que quiera a�adir el usuario del motor
	se implementar� como componente, y para usarla se a�adir� a un Object.
*/
class Component {
protected:

	/**
		Puntero al Object al que pertenecen.
		Una instancia de Component solo puede pertenecer a un Object.
		No se podr� cambiar de Object una vez creado.
	*/
	Object* gameObject = nullptr;

	/**
		Nombre de la clase que hereda de Component.
		Es obligatorio darle un valor a esta variable en el constructor de
		la clase que la herede.
		El nombre debe ser el mismo para todas las instancias de una misma clase.
	*/
	std::string type;

	/**
		Este m�todo se llama cuando se destruye un componente.
		Debe tratarse como el destructor de la clase y no declarar un destructor de verdad.
	*/
	virtual void destroy();

public:

	/**
		Este m�todo se llama una vez cada frame
	*/
	virtual void update();
	bool enabled;
	std::string getType();
	~Component();
	void setGameObject(Object* obj);
	Object* getGameObject();
};