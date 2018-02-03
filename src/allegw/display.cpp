#include <stdexcept>
#include <allegro5/allegro.h>
#include "headers/app.hpp"
using namespace allegw;

display::display(): display_ptr{nullptr, deleter{}}, events{nullptr} {
    al_init_timeout(&timeout, 0.06);
    if (auto ptr = al_create_display(width, height); ptr != nullptr) { 
        display_ptr.reset(ptr);
        if (events = al_create_event_queue(); events != nullptr) {
            al_register_event_source(events, al_get_display_event_source(ptr));
        }
        else throw std::runtime_error{"event queue creation failed."};
    }
    else throw std::runtime_error{"display creation failed."};
}

void display::wait_and_draw() noexcept {
    al_flip_display();
}

bool display::is_time_to_close() noexcept {
    static ALLEGRO_EVENT event;
    if(auto got = al_wait_for_event_until(events, &event, &timeout);
            got && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return true;
    else return false;
}

void display::deleter::operator()(ALLEGRO_DISPLAY* disp) const {
    al_destroy_display(disp);;
}

std::unique_lock<std::recursive_mutex> display::get_lock() {
    return std::unique_lock<std::recursive_mutex>{mutex};
}
