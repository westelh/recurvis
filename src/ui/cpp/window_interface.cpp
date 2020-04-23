#include "spdlog/spdlog.h"
#include "window_interface.hpp"


window_interface::window_interface(int w, int h) {
    spdlog::info("New window created width:{}, height:{}", w, h);
}


// TODO: if updater is stateless, make update() static method
void window_interface::window_updater::update(std::unique_ptr<window_interface> &window) {
    window->update();
}