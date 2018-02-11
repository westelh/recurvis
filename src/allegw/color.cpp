#include "headers/color.hpp"
using namespace recurvis::allegw;

std::unique_lock<std::recursive_mutex> color::get_lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>{mutex};
}

color::color(const color::data_type& c): col{c} {  } 
color::color(color::data_type&& c): col{c} { }
color::color(const color& c): col{c.red(), c.green(), c.blue(), c.alpha()}, mutex{} {  }


color& color::operator=(const color& rhs) noexcept {
    this->red(rhs.red());
    this->green(rhs.green());
    this->blue(rhs.blue());
    this->alpha(rhs.alpha());
    return *this;
}

color& color::operator=(color&& rhs) noexcept {
    this->red(rhs.red());
    this->green(rhs.green());
    this->blue(rhs.blue());
    this->alpha(rhs.alpha());
    return *this;
}

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

int color::alpha() const noexcept {
    return std::get<3>(col);
}

void color::alpha(int a) noexcept {
    auto lock = get_lock();
    std::get<3>(col) = a;
}

ALLEGRO_COLOR recurvis::allegw::convert(const recurvis::allegw::color& c) noexcept {
    return al_map_rgba(c.red(), c.green(), c.blue(), c.alpha());
}

ALLEGRO_COLOR recurvis::allegw::convert(recurvis::allegw::color&& c) noexcept {
    return al_map_rgba(c.red(), c.green(), c.blue(), c.alpha());
}

