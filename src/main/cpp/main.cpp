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
    app->add_window(800, 600);
    app->add_window(41, 444);
    app->main_loop();
}
