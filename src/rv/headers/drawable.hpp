#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <map>
#include <mutex>

namespace recurvis {
    using coord = std::pair<int, int>;
    
    class drawable {
        coord pos;
        mutable std::recursive_mutex mutex;
    protected:
        std::unique_lock<std::recursive_mutex> get_lock() const noexcept;
    public:
        drawable(const coord&);
        drawable(coord&&);
        ~drawable() = default;
        coord get_pos() const noexcept;
        void set_pos(const coord&) noexcept;
        void set_pos(coord&&) noexcept;
        virtual void draw() = 0;
    };
}

#endif
