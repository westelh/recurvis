#include "headers/drawable.hpp"

std::unique_lock<std::recursive_mutex> recurvis::allegw::drawable::get_lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>(mutex);
}

recurvis::allegw::drawable::drawable(const coord& p, const color& c): pos{p}, col{c} {  }
recurvis::allegw::drawable::drawable(coord&& p, allegw::color&& c): pos{p}, col{c} {  }

recurvis::allegw::coord recurvis::allegw::drawable::get_pos() const noexcept { return pos; }

void recurvis::allegw::drawable::set_pos(const coord& c) noexcept {
    auto lock = get_lock();
    pos = c;
}
void recurvis::allegw::drawable::set_pos(coord&& c) noexcept {
    auto lock = get_lock();
    pos = c;
}

recurvis::allegw::color recurvis::allegw::drawable::get_color() const noexcept {
    return recurvis::allegw::color{col};
}

void recurvis::allegw::drawable::set_color(const allegw::color& c) noexcept {
    auto lock = get_lock();
    col = c;
}

void recurvis::allegw::drawable::set_color(allegw::color&& c) noexcept {
    auto lock = get_lock();
    col = c;
}
