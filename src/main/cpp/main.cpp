#include <memory>
#include <opengl_app.h>
#include "spdlog/spdlog.h"
#include "app_interface.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    auto app = std::unique_ptr<app_interface>(new opengl_app{});
    app->add_window(800, 600);
    app->add_window(41, 444);
    spdlog::info("{04d}", 23);
    app->main_loop();
}
