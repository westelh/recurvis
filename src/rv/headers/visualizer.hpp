#ifndef INCLUDE_VISUALIZER_HPP
#define INCLUDE_VISUALIZER_HPP

#include <vector>
#include <mutex>
#include "./card.hpp"

namespace recurvis {
    class visualizer {
        mutable std::recursive_mutex mutex;
        std::unique_lock<std::recursive_mutex> lock() const noexcept;
        std::vector<card> cards;
    public:
        void notify_new_node() noexcept;
        void visualize() noexcept;
    };
}

#endif
