#include "window.hpp"

window::window(int w, int h) : close_flag_m{false}, update_thread_m{[this, &w, &h](){
    resize(w,h);
    while(!close_flag_m)  {
        update();
    }   
}} { }

void window::close() noexcept {
    close_flag_m.store(true);
}

void window::close_and_wait() noexcept {
    window::close();
    update_thread_m.join();
}