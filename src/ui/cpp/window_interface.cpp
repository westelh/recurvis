#include "window_interface.hpp"

window_interface::window_interface([[maybe_unused]]int w, [[maybe_unused]]int h) {

}

void window_interface::close() noexcept {
}

void window_interface::close_and_wait() noexcept {
    window_interface::close();
}

void window_interface::request_stop_update_thread() noexcept {
}

window_interface::~window_interface() {
    stop_update_thread_and_wait();
}

void window_interface::stop_update_thread_and_wait() noexcept {
    request_stop_update_thread();
}

// TODO: if updater is stateless, make update() static method
void window_interface::window_updater::update(std::unique_ptr<window_interface> &window) {
    window->update();
}
