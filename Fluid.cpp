#include "Fluid.h"

Fluid::Fluid()
: particles(), sphere() {

}

void Fluid::intialize()
{
	sphere.createVBO();
}

void Fluid::tick() {

}

void Fluid::draw(EZGL::ShaderProgram* prog, EZGL::Camera* cam) {
	prog->setViewProjMatrix(cam->getViewProj());

	prog->draw(sphere);
}