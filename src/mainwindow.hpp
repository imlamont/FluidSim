#pragma once

#include <FL/Fl_Gl_Window.H>

class MainWindow : public Fl_Gl_Window {
    void draw();
    //int handle(int);
public:
    MainWindow(int width, int height, const char* label);
    ~MainWindow();
};