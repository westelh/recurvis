#include "glfw_with_vulkan.h"
#include "glfw_error.h"
#include "opengl_window.h"
#include "opengl_app.h"

bool opengl_app::initialized = false;

opengl_app::opengl_app() : app_interface() {
    if (initialized) return;

    if (!glfwInit()) throw glfw_error::since_last_call();
    else initialized = true;
}

std::unique_ptr<window_interface> opengl_app::create_window(int w, int h) {
    return std::make_unique<opengl_window>(w, h);
}

opengl_app::~opengl_app() {
    glfwTerminate();
}

void opengl_app::main_loop() {
    while (!should_exit_loop()) {
        remove_closing_windows();
        update_all_windows();
        std::this_thread::sleep_for(window_interface::wait);
    }
}
