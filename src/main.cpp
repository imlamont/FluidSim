#include <FL/Fl.h>
#include "mainwindow.hpp"

int main(int argc, char** argv) {
    MainWindow mainWindow(200,200,"main");
    mainWindow.show();

    Fl::run();

    return 0;
}