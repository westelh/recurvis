#include "headers/color.hpp"
using namespace recurvis::allegw;

std::unique_lock<std::recursive_mutex> color::get_lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>{mutex};
}

color::color(const color::data_type& c): col{c} {  } 
color::color(color::data_type&& c): col{c} { }

int color::red() const noexcept {
    return std::get<0>(col);
}

void color::red(int r) noexcept {
    auto lock = get_lock();
    std::get<0>(col) = r;
}

int color::green() const noexcept {
    return std::get<1>(col);
}

void color::green(int g) noexcept {
    auto lock = get_lock();
    std::get<1>(col) = g;
}

int color::blue() const noexcept {
    return std::get<2>(col);
}

void color::blue(int b) noexcept {
    auto lock = get_lock();
    std::get<2>(col) = b;
}
