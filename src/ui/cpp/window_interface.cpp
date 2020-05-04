#include "spdlog/spdlog.h"
#include "AbstractWindow.hpp"


AbstractWindow::AbstractWindow(int w, int h) {
    spdlog::info("New window created width:{}, height:{}", w, h);
}


// TODO: if updater is stateless, make update() static method
void AbstractWindow::window_updater::update(std::shared_ptr<AbstractWindow> &window) {
    window->update();
}