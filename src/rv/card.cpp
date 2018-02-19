#include "./headers/card.hpp"

recurvis::card::card(const recurvis::allegw::coord& c): rect{c} {  }
recurvis::card::card(recurvis::allegw::coord&& c): rect{c} {  }

void recurvis::card::draw() noexcept {
    rect.draw();
}
