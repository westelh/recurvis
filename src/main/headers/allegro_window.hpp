#ifndef INCLUDE_WINDOW_HPP
#define INCLUDE_WINDOW_HPP

#include <thread>
#include "allegro5/allegro.h"
#include "window.hpp"

// forward declaration
class app;

class allegro_window final : public window {
    ALLEGRO_DISPLAY* display_m;

    virtual void update() override;
public:
    allegro_window(int w, int h);
    ~allegro_window();

    virtual void close() noexcept override;
};

#endif
