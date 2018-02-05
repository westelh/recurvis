#include <stdexcept>
#include <allegro5/allegro.h>
#include "headers/app.hpp"
using namespace allegw;

namespace {
    ALLEGRO_DISPLAY* get_display() {
        if(auto r = al_create_display(display::width, display::height); r != nullptr)
            return r;
        else throw std::runtime_error{"display creation failed."};
    }

    ALLEGRO_TIMEOUT get_timeout(float t) noexcept {
        ALLEGRO_TIMEOUT timeout; 
        al_init_timeout(&timeout, t);
        return timeout;
    }
}

display::display(): display_ptr{get_display(),deleter{}},
    events{nullptr},
    timeout{get_timeout(0.06)} {
    if (events = al_create_event_queue(); events != nullptr)
            al_register_event_source(events, al_get_display_event_source(display_ptr.get()));
    else throw std::runtime_error{"event queue creation failed."};
}

void display::wait_and_draw() noexcept {
    auto lock = get_lock();
    al_flip_display();
}

bool display::is_time_to_close() const noexcept {
    auto lock = get_lock();
    static ALLEGRO_EVENT event;
    if(auto got = al_wait_for_event_until(events, &event, &timeout);
            got && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return true;
    else return false;
}

void display::deleter::operator()(ALLEGRO_DISPLAY* disp) const {
    al_destroy_display(disp);
}

const std::unique_lock<std::recursive_mutex> display::get_lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>{mutex};
}
