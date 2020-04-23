#include <GLFW/glfw3.h>
#include <glfw_error.h>
#include <opengl_window.h>
#include "opengl_app.h"

bool opengl_app::initialized = false;

opengl_app::opengl_app() : app_interface() {
    if (initialized) return;

    if (!glfwInit()) throw glfw_error::since_last_call();
    else initialized = true;
}

std::shared_ptr<window_interface> opengl_app::create_window(int w, int h) {
    return std::make_shared<opengl_window>(w, h);
}

opengl_app::~opengl_app() {
    glfwTerminate();
}
