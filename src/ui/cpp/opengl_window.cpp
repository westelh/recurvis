#include <GLFW/glfw3.h>
#include <glfw_error.h>
#include "opengl_window.h"

opengl_window::opengl_window(int w, int h, const char *title) : window_interface(w, h), window{nullptr} {
    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (window == nullptr) throw glfw_error::since_last_call();

    glfwMakeContextCurrent(window);
}

opengl_window::~opengl_window() {
    glfwDestroyWindow(window);
}

void opengl_window::update() {
    /* Render here */
    //glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    std::this_thread::sleep_for(wait);
}

bool opengl_window::resize(int w, int h) const {
    glfwSetWindowSize(window, w, h);
    return false;
}

void opengl_window::close() noexcept {
    window_interface::close();
}

void opengl_window::close_and_wait() noexcept {
    window_interface::close_and_wait();
}

bool opengl_window::is_closing() {
    return glfwWindowShouldClose(window);
}
