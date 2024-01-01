#pragma once
#include <Windows.h>
#include <unordered_set>
#include "Particle.h"
#include <EZGL/ShaderProgram.h>
#include <EZGL/Camera.h>
#include "Sphere.h"

class MainWindow;

class Fluid
{
	friend class MainWindow;
private:
	std::unordered_set<Particle, ParticleHash> particles;
	Sphere sphere;

	void intialize();
	void tick();
	void draw(EZGL::ShaderProgram* prog, EZGL::Camera* cam);
public:
	Fluid();

};

