#include <FL/Fl.h>
#include "mainwindow.hpp"

constexpr int FRAMERATE_MS = 1000 / 60;

void redraw_callback (void* param_ptr) {
    Fl_Widget* widget = static_cast<Fl_Widget*>(param_ptr);

    widget->redraw();
    Fl::repeat_timeout(FRAMERATE_MS / 1000, redraw_callback, param_ptr);
}

int main(int argc, char** argv) {
    MainWindow mainWindow(200,200,"main");
    mainWindow.show();

    Fl::add_timeout(FRAMERATE_MS / 1000, redraw_callback, &mainWindow);
    Fl::run();

    return 0;
}
