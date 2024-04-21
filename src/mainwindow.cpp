#include "mainwindow.hpp"

MainWindow::MainWindow(int width, int height, const char* label)
: Fl_Gl_Window(width, height, label) {
    mode(FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE | FL_OPENGL3);
}

MainWindow::~MainWindow() {}

void MainWindow::draw() {

}