#ifndef INCLUDE_WINDOW_HPP
#define INCLUDE_WINDOW_HPP

#include "allegro5/allegro.h"

namespace allegro_wrapper {
    class app;

    class window final {
            friend class app; 
            window(int w, int h);
            ALLEGRO_DISPLAY* display;
        public:
    };
}

#endif
