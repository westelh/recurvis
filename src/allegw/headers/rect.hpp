#ifndef RECT_HPP
#define RECT_HPP

#include "drawable.hpp"

namespace recurvis::allegw {
    class rect: public drawable {
        int width_m;
        int height_m;
    public:
        rect(const coord& c);
        rect(coord&&);
        int width() const noexcept;
        void width(int) noexcept;
        int height() const noexcept;
        void height(int) noexcept;
        void draw() override;
    };
}

#endif
