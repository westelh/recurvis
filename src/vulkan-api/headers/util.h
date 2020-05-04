#ifndef RECURVIS_UTIL_H
#define RECURVIS_UTIL_H

#include <algorithm>
#include <type_traits>
#include <string>

namespace recurvis {
    template<class T, template<class...> class Container, class Func>
    inline auto apply(const Container<T> &container, Func f) -> Container<typename std::invoke_result<Func, T>::type> {
        Container<typename std::invoke_result<Func, T>::type> buffer;
        std::transform(std::begin(container), std::end(container), std::back_inserter(buffer), f);
        return buffer;
    }

    std::string removeUTF8Assurance(std::u8string_view str) noexcept;
}


#endif //RECURVIS_UTIL_H
