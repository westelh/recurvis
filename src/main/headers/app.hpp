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

            template <class F>
            window create_window(int w, int h, F fun) {
                return window{w, h, fun};
            }
    };
}

#endif
