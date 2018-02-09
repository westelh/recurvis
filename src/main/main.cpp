#include <allegro5/allegro.h>
#include "../allegw/headers/app.hpp"
#include "../rv/headers/rect.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    recurvis::allegw::app app;
    auto display = app.make_display();
    recurvis::rect r{recurvis::coord{1,1}};
    int counter = 0;
    while(!display.is_time_to_close()) {
        r.set_pos(recurvis::coord{800, 400});
        r.width(static_cast<int>(counter/50));
        r.height(static_cast<int>(counter/50));
        r.draw();
        display.wait_and_draw();
        counter++;
    }
    return true;
}
