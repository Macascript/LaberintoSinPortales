#include "orbitalLight.h"

void OrbitalLight::step(){
    angle += 0.01f;
    position.x = cos(angle) * front.x + sin(angle) * front.z + orbitalCentre.x;
	position.z = -sin(angle) * front.x + cos(angle) * front.z + orbitalCentre.z;


	/*
	float auxAngle = 0.0f;
	bool forward = true;

	if(auxAngle == angle){
		forward = false;
		auxAngle -= 0.001f;
	}
	else if(auxAngle == 0){
		forward = true;
		auxAngle += 0.001f;
	}

	if(forward){
		position.x = cos(0.001f) * (position - orbitalCentre).x + sin(0.001f) * (position - orbitalCentre).z;
		position.z = -sin(0.001f) * (position - orbitalCentre).x + cos(0.001f) * (position - orbitalCentre).z;
		auxAngle += 0.001f;
	}
	else{
		position.x = cos(-0.001f) * (position - orbitalCentre).x + sin(-0.001f) * (position - orbitalCentre).z;
		position.z = -sin(-0.001f) * (position - orbitalCentre).x + cos(-0.001f) * (position - orbitalCentre).z;
		auxAngle -= 0.001f;
	}
		
   	*/
}