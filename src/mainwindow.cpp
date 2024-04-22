#include "mainwindow.hpp"
#include "../lib/ezgl/lib/glew/include/GL/glew.h"
#include <iostream>

MainWindow::MainWindow(int width, int height, const char* label)
: Fl_Gl_Window(width, height, label), 
prog(), 
cam(glm::vec3(0,0,0), glm::vec3(-1,0,0)),
sphere() {
    mode(FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE | FL_OPENGL3);
}

bool MainWindow::initializeGL() {
    // initalize opengl
    if (first) {
        first = 0;
        make_current();

        GLenum err = glewInit();
        if (err != GLEW_OK) {
            const GLubyte* str = glewGetErrorString(err);
            std::cerr << "glew initalization error: " << str;
            return false;
        }
        
        glViewport(0, 0, w(), h());
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    return true;
}

bool MainWindow::initializeProgsAndObjs() {
    // initalize program
    // NOTE: this is runtime path 
    prog.create("../../shaders/vert.glsl","../../shaders/frag.glsl");
    prog.setModelMatrix(glm::mat4(glm::vec4(1,0,0,0),
                                  glm::vec4(0,1,0,0),
                                  glm::vec4(0,0,1,0),
                                  glm::vec4(0,0,0,1)));

    sphere.createVBO();

    return true;
}

MainWindow::~MainWindow() {}

void MainWindow::draw() {
    prog.draw(sphere);
}

int MainWindow::handle(int event) {
    switch (event) {
        case (FL_SHOW):
            if (!initializeGL() || !initializeProgsAndObjs()) {
                hide();
                return 0;
            }
            return Fl_Gl_Window::handle(event);
        default:
            return Fl_Gl_Window::handle(event);
    }
}