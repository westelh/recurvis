#include <thread>
#include "window.hpp"

window::window(int w, int h) : close_flag_m{false}, update_thread_m{[this](){
    while(!close_flag_m)  {
        update();
    }   
}} { }

window::~window() {

}

void window::close() noexcept {
    close_flag_m.store(true);
}

void window::close_and_wait() noexcept {
    window::close();
    update_thread_m.join();
}