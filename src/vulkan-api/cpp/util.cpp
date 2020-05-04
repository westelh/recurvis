#include "util.h"

std::string recurvis::removeUTF8Assurance(std::u8string_view str) noexcept {
    return std::string(reinterpret_cast<const char *>(str.data()));
}