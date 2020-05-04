#include "glfw_with_vulkan.h"
#include "glfw_error.h"
#include "GlfwWindow.h"

GlfwWindow::GlfwWindow(int w, int h, const char *title) : AbstractWindow(w, h), window{nullptr} {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (window == nullptr) throw glfw_error::since_last_call();
}

GlfwWindow::~GlfwWindow() {
    glfwDestroyWindow(window);
}

void GlfwWindow::update() {
    /* Render here */
    //glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

bool GlfwWindow::resize(int w, int h) const {
    glfwSetWindowSize(window, w, h);
    return false;
}

bool GlfwWindow::is_closing() {
    return glfwWindowShouldClose(window);
}

void GlfwWindow::close() noexcept {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLFWwindow *GlfwWindow::getWindowHandle() const {
    return window;
}
