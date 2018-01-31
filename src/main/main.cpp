#include <allegro5/allegro.h>
#include "../allegw/headers/app.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    allegw::app app;
    allegw::display&& display = app.make_display();
    while(!display.is_time_to_close()) {
        display.wait_and_draw();
    }
    return true;
}
