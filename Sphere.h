#pragma once

#include <EZGL/InstancedDrawable.h>
#include <glm/glm.hpp>

#define SPHERE_DETAIL 10
#define SPHERE_RADIUS 1.f
#define PI 3.14159265f
#define TAU (2.0f * PI)

class Sphere : public EZGL::InstancedDrawable {
public:
	Sphere();

	void createVBO();
};

