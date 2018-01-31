#include <stdexcept>
#include <cstdlib>
#include <string>
#include <allegro5/allegro.h>
#include "headers/init.hpp"
using namespace std::string_literals;
using namespace allegw;

namespace {
    void on_exit() {
        al_uninstall_system();
    }
}

app::app() { 
    std::atexit(on_exit);
    if(al_install_system(ALLEGRO_VERSION_INT, nullptr) != true)
        throw std::runtime_error{"allegro initialization failed."};
    al_set_app_name(appname.c_str());
}

app::~app() {
    al_uninstall_system();
}

display::display() {
    display_ptr = al_create_display(width, height);
    if (display_ptr == nullptr)
        throw std::runtime_error{"display creation failed."};
}

display::~display() {
    al_destroy_display(display_ptr);
}

display&& app::make_display() {
    return std::move(display{});
}
