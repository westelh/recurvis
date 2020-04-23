#ifndef INCLUDE_WINDOW_HPP
#define INCLUDE_WINDOW_HPP

#include <thread>
#include "window_interface.hpp"

struct ALLEGRO_DISPLAY;

class allegro_window final : public window {
    ALLEGRO_DISPLAY* display_m;

    void update() override;

protected:
    bool resize(int w, int h) const override;

public:
    allegro_window(int w, int h);
    ~allegro_window() override;

    void close() noexcept override;
};

#endif
