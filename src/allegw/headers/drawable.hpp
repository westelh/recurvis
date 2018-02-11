#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <map>
#include <mutex>
#include "color.hpp"

namespace recurvis {
    using coord = std::pair<int, int>;
    
    class drawable {
        coord pos;
        allegw::color col;
        mutable std::recursive_mutex mutex;
    protected:
        std::unique_lock<std::recursive_mutex> get_lock() const noexcept;
    public:
        drawable(const coord&, const allegw::color&);
        drawable(coord&&, allegw::color&&);
        ~drawable() = default;
        coord get_pos() const noexcept;
        void set_pos(const coord&) noexcept;
        void set_pos(coord&&) noexcept;
        allegw::color get_color() const noexcept;
        void set_color(const allegw::color& c) noexcept;
        void set_color(allegw::color&& c) noexcept;
        virtual void draw() = 0;
    };
}

#endif
