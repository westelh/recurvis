#ifndef RECURVIS_GLFWWINDOW_H
#define RECURVIS_GLFWWINDOW_H

#include "AbstractWindow.hpp"

struct GLFWwindow;

class GlfwWindow : public AbstractWindow {
    GLFWwindow *window;

public:
    GlfwWindow(int w, int h, const char *title = "Window");

    ~GlfwWindow() override;

    [[nodiscard]] GLFWwindow *getWindowHandle() const;

    void close() noexcept override;

    bool is_closing() override;

protected:
    void update() override;

    [[nodiscard]] bool resize(int w, int h) const override;
};


#endif //RECURVIS_GLFWWINDOW_H
