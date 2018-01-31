#include <stdexcept>
#include <allegro5/allegro.h>
#include "headers/app.hpp"
using namespace allegw;

display::display() {
    display_ptr = al_create_display(width, height);
    if (display_ptr == nullptr)
        throw std::runtime_error{"display creation failed."};
}

display::~display() {
    al_destroy_display(display_ptr);
}

void display::wait_and_draw() noexcept {
    al_flip_display();
}

