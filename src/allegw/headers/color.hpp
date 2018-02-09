#ifndef RECURVIS_COLOR_HPP
#define RECURVIS_COLOR_HPP

#include <tuple>
#include <mutex>

namespace recurvis::allegw {
    class color {
    public:
        using data_type = std::tuple<int, int, int>;
    private:
        data_type col;
        mutable std::recursive_mutex mutex;
        std::unique_lock<std::recursive_mutex> get_lock() const noexcept;
    public:
        color(const data_type&);
        color(data_type&&);
        int red() const noexcept;
        void red(int) noexcept;
        int green() const noexcept;
        void green(int) noexcept;
        int blue() const noexcept;
        void blue(int) noexcept;
    };
}

#endif
