#pragma once

#include <FL/Fl_Gl_Window.H>

#include "../lib/ezgl/ShaderProgram.hpp"
#include "../lib/ezgl/Camera.hpp"
#include "sphere.hpp"

class MainWindow : public Fl_Gl_Window {
private:
    inline static bool first = true;

    EZGL::ShaderProgram prog;
    EZGL::Camera cam;
    Sphere sphere;

    bool initializeGL();
    bool initializeProgsAndObjs();

public:
    MainWindow(int width, int height, const char* label);
    ~MainWindow();
    
    void draw();
    int handle(int);
};