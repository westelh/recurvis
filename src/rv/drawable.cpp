#include "headers/drawable.hpp"
using namespace recurvis;

std::unique_lock<std::recursive_mutex> drawable::get_lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>(mutex);
}

drawable::drawable(const coord& p): pos{p} {  }
drawable::drawable(coord&& p): pos{p}{  }

coord drawable::get_pos() const noexcept { return pos; }

void drawable::set_pos(const coord& c) noexcept {
    auto lock = get_lock();
    pos = c;
}
void drawable::set_pos(coord&& c) noexcept {
    auto lock = get_lock();
    pos = c;
}
