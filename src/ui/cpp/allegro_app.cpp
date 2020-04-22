#include <stdexcept>
#include "allegro5/allegro.h"
#include "allegro_window.hpp"
#include "allegro_app.hpp"

allegro_app::allegro_app() {
    if (!al_init()) throw std::runtime_error{"Initialization of base system failed"};
}

allegro_app::~allegro_app() {

}

std::unique_ptr<window> allegro_app::create_window(int w, int h) {
    return std::make_unique<allegro_window>(w, h);
}