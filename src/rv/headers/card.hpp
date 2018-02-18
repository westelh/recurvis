#ifndef INCLUDE_CARD_HPP
#define INCLUDE_CARD_HPP

#include "../../allegw/headers/rect.hpp"

namespace recurvis {
    class card {
        allegw::rect rect;
    public:
        card();
        void draw() noexcept;
    };
}

#endif
