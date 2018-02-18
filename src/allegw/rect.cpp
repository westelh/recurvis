#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "headers/rect.hpp"

recurvis::allegw::rect::rect(const coord& c): drawable(c, std::make_tuple(50, 0, 0, 100)),
    width_m{100}, height_m{100} {  }
recurvis::allegw::rect::rect(coord&& c): drawable(c, std::make_tuple(50, 0, 0, 100)),
    width_m{100}, height_m{100} {  }

int recurvis::allegw::rect::width() const noexcept {
    return width_m;
}

void recurvis::allegw::rect::width(int w) noexcept {
    auto lock = get_lock();
    width_m = w;
}

int recurvis::allegw::rect::height() const noexcept {
    return height_m;
}

void recurvis::allegw::rect::height(int h) noexcept {
    auto lock = get_lock();
    height_m = h;
}

void recurvis::allegw::rect::draw() {
    auto [x, y] = get_pos();
    al_draw_filled_rectangle(x, y, x+width(), y+height(), allegw::convert(get_color()));
}
