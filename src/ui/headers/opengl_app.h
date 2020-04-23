#ifndef RECURVIS_OPENGL_APP_H
#define RECURVIS_OPENGL_APP_H

#include "app_interface.hpp"

class opengl_app : public app_interface {
    static bool initialized;
public:
    opengl_app();

    ~opengl_app() override;

    std::unique_ptr<window_interface> create_window(int w, int h) override;

    void main_loop() override;
};


#endif //RECURVIS_OPENGL_APP_H
