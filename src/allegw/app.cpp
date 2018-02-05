#include <stdexcept>
#include <cstdlib>
#include <allegro5/allegro.h>
#include "headers/app.hpp"

using namespace recurvis::allegw;

namespace {
    // to be called when it is shutting down.
    void on_exit() {
        al_uninstall_system();
    }
}

app::app() { 
    // set uninstalling process.
    std::atexit(on_exit);
    // master initialization.
    if(al_install_system(ALLEGRO_VERSION_INT, nullptr) != true)
        throw std::runtime_error{"allegro initialization failed."};
    al_set_app_name(appname.c_str());
}

app::~app() noexcept {
    al_uninstall_system();
}

display app::make_display() {
    return display{};
}
