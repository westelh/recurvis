#ifndef INCLUDE_APP_HPP
#define INCLUDE_APP_HPP

#include <string>
#include <memory>
#include "window.hpp"

namespace allegro_wrapper {
    class app final {
            static bool initialized;
            static void init();
        public:
            app();
            window create_window(int w, int h);
    };
}

#endif
