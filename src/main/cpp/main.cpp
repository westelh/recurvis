#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <opengl_app.h>
#include "app_interface.hpp"
#include "window_updater.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    auto app = std::unique_ptr<app_interface>(new opengl_app{});
    auto window = app->create_window(800, 600);
    window_updater updater(window);

    updater.loop();

    std::this_thread::sleep_for(std::chrono::seconds(10));
}
