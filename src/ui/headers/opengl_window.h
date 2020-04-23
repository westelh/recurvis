#ifndef RECURVIS_OPENGL_WINDOW_H
#define RECURVIS_OPENGL_WINDOW_H

#include "window_interface.hpp"

struct GLFWwindow;

class opengl_window : public window_interface {
    GLFWwindow* window;

public:
    opengl_window(int w, int h, const char *title = "Window");

    ~opengl_window() override;

    void close() noexcept override;

    void close_and_wait() noexcept override;

    bool is_closing() override;

protected:
    void update() override;

    bool resize(int w, int h) const override;
};


#endif //RECURVIS_OPENGL_WINDOW_H
