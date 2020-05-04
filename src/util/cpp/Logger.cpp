#include <Logger.h>

std::string recurvis::Logger::passWithoutCodeCvt(std::u8string_view str) {
    return std::string{reinterpret_cast<const char *>(str.data())};
}
