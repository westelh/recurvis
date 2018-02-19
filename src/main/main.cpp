#include <thread>
#include <allegro5/allegro.h>
#include "../allegw/headers/app.hpp"
#include "../rv/headers/visualizer.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    recurvis::allegw::app app;
    recurvis::visualizer vis;
    std::thread th{[&](){
        auto display = app.make_display();
        vis.notify_new_node();
        while(!display.is_time_to_close()) {
            display.clear();
            vis.notify_new_node();
            vis.visualize();
            display.wait_and_draw();
        }
    }};
    th.join();
    return true;
}
