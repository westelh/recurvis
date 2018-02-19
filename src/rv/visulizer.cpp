#include "./headers/visualizer.hpp"

std::unique_lock<std::recursive_mutex> recurvis::visualizer::lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>{mutex};
}

void recurvis::visualizer::notify_new_node() noexcept {
    auto l = lock();
    cards.emplace_back(allegw::coord{cards.size()+30, cards.size()+30});
}

void recurvis::visualizer::visualize() noexcept {
    for (auto&& i : cards) {
        i.draw();
    }
}
