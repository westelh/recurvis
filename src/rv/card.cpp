#include "./headers/card.hpp"

recurvis::card::card(): rect{allegw::coord{20, 20}} {

}

void recurvis::card::draw() noexcept {
    rect.draw();
}
