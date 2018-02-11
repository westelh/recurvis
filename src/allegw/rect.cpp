#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "headers/rect.hpp"
using namespace recurvis;

rect::rect(const coord& c): drawable(c, allegw::color{std::make_tuple(50, 0, 0, 100)}), width_m{100}, height_m{100} {  }
rect::rect(coord&& c): drawable(c, allegw::color{std::make_tuple(50, 0, 0, 100)}), width_m{100}, height_m{100} {  }

int rect::width() const noexcept {
    return width_m;
}

void rect::width(int w) noexcept {
    auto lock = get_lock();
    width_m = w;
}

int rect::height() const noexcept {
    return height_m;
}

void rect::height(int h) noexcept {
    auto lock = get_lock();
    height_m = h;
}

void rect::draw() {
    auto [x, y] = get_pos();
    al_draw_rectangle(x, y, x+width(), y+height(), allegw::convert(get_color()), 55);
}
