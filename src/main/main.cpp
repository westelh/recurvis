#include <allegro5/allegro.h>
#include "../allegw/headers/app.hpp"
#include "../allegw/headers/rect.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    recurvis::allegw::app app;
    auto display = app.make_display();
    recurvis::rect r{recurvis::coord{1,1}};
    int counter = 0;
    while(!display.is_time_to_close()) {
        display.clear();
        r.set_pos(recurvis::coord{r.get_pos().first+1, r.get_pos().second});
        r.draw();
        display.wait_and_draw();
        counter++;
    }
    return true;
}
