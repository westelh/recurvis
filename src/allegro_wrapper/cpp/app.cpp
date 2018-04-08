#include <stdexcept>
#include "allegro5/allegro.h"
#include "app.hpp"

bool allegro_wrapper::app::initialized = false;

void allegro_wrapper::app::init() {
    if (!al_init()) throw std::runtime_error{"Initialization of base system failed"};
    initialized = true;
}

allegro_wrapper::app::app() {
    if (!initialized) init();
}
