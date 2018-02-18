#include <allegro5/allegro.h>
#include "../allegw/headers/app.hpp"
#include "../rv/headers/card.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    recurvis::allegw::app app;
    auto display = app.make_display();
    auto card = recurvis::card{};
    while(!display.is_time_to_close()) {
        display.clear();
        card.draw();
        display.wait_and_draw();
    }
    return true;
}
