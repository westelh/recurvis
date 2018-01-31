#include <allegro5/allegro.h>
#include "../allegw/headers/app.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    allegw::app app;
    auto display = app.make_display();
    return true;
}
