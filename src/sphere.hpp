#pragma once

#include "../lib/ezgl/InstancedDrawable.hpp"
#include <glm/glm.hpp>

class Sphere : public EZGL::InstancedDrawable {
public:
    static constexpr int SPHERE_DETAIL = 10;
    static constexpr float SPHERE_RADIUS = 1.f;
    static constexpr float PI = 3.1415926f;
    static constexpr float TAU = (2.0 * PI);

	Sphere();

	void createVBO();
};