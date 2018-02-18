#include <thread>
#include <allegro5/allegro.h>
#include "../allegw/headers/app.hpp"
#include "../rv/headers/card.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    recurvis::allegw::app app;
    auto card = recurvis::card{};
    std::thread th{[&](){
        auto display = app.make_display();
        while(!display.is_time_to_close()) {
            display.clear();
            card.draw();
            display.wait_and_draw();
        }
    }};
    th.join();
    return true;
}
