#include "window_interface.hpp"

window_interface::window_interface([[maybe_unused]]int w, [[maybe_unused]]int h) : close_flag_m{false}, update_thread_m{[this](){
    while(!close_flag_m)  {
        //update();
    }
}} { }

void window_interface::close() noexcept {
    close_flag_m.store(true);
}

void window_interface::close_and_wait() noexcept {
    window_interface::close();
    update_thread_m.join();
}

void window_interface::request_stop_update_thread() noexcept {
    close_flag_m.store(true);
}

window_interface::~window_interface() {
    stop_update_thread_and_wait();
}

void window_interface::stop_update_thread_and_wait() noexcept {
    request_stop_update_thread();
    update_thread_m.join();
}
