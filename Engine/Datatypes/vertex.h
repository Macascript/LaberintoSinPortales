#pragma once
#define OpenGLsystem
#include "Vec4/vec4.h"
#include "Vec2/vec2.h"

typedef struct vertex_t{

	Vec4 posicion;
	Vec4 color;
	Vec4 normal;
	Vec2 texCoord;
}vertex_t;