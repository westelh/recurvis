#include "allegro5/allegro.h"
#include "allegro_window.hpp"

allegro_window::allegro_window(int w, int h): window(w, h), display_m{nullptr} {
    auto* ptr = al_create_display(w, h);

    if (ptr != nullptr) display_m = ptr;
    else throw std::runtime_error{"Window creation failed."};
}

allegro_window::~allegro_window() {
    close_and_wait();
    al_destroy_display(display_m);
}

void allegro_window::update() {
}

void allegro_window::close() noexcept {
    window::close();
}