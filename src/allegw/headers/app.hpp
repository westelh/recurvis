#pragma once

#include <string>
#include "display.hpp"

namespace allegw {
    class app {
        static inline const std::string appname = "recurvis";
    public:
        app();
        ~app() noexcept;
        // make an instance of display.
        display make_display();
    };
}
