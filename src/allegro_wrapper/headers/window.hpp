#ifndef INCLUDE_WINDOW_HPP
#define INCLUDE_WINDOW_HPP

#include <thread>
#include "allegro5/allegro.h"

namespace allegro_wrapper {
    class app;

    class window final {
            friend class app; 

            template <class F>
            window(int w, int h, F f);

            ALLEGRO_DISPLAY* display;
            std::thread* th;
            bool stop;
        public:
            ~window();
    };
}

template <class F>
allegro_wrapper::window::window(int w, int h, F f): stop{false} {
    auto* ptr = al_create_display(w, h);
    if (ptr != nullptr) display = ptr;
    else throw std::runtime_error{"Window creation failed."};
    th = new std::thread{[&,this](){
        while(stop) {
            f();
        }
    }};
}

allegro_wrapper::window::~window() {
    stop = true;
    th->join();
    al_destroy_display(display);
}

#endif
