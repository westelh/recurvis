#include "headers/drawable.hpp"
using namespace recurvis;

std::unique_lock<std::recursive_mutex> drawable::get_lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>(mutex);
}

drawable::drawable(const coord& p, const allegw::color& c): pos{p}, col{c} {  }
drawable::drawable(coord&& p, allegw::color&& c): pos{p}, col{c} {  }

coord drawable::get_pos() const noexcept { return pos; }

void drawable::set_pos(const coord& c) noexcept {
    auto lock = get_lock();
    pos = c;
}
void drawable::set_pos(coord&& c) noexcept {
    auto lock = get_lock();
    pos = c;
}

allegw::color drawable::get_color() const noexcept {
    return allegw::color{col};
}

void drawable::set_color(const allegw::color& c) noexcept {
    auto lock = get_lock();
    col = c;
}

void drawable::set_color(allegw::color&& c) noexcept {
    auto lock = get_lock();
    col = c;
}
