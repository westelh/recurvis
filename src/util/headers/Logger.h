#ifndef RECURVIS_LOGGER_H
#define RECURVIS_LOGGER_H

#include <string_view>
#include <sstream>
#include <spdlog/spdlog.h>

namespace recurvis {
    namespace Logger {
        template<class... Args>
        void debug(std::string_view domain, std::string_view msg, Args... args) {
            std::stringstream ss;
            ss << "[@" << domain << "] " << msg;
            spdlog::debug(ss.str().c_str(), args...);
        }

        std::string passWithoutCodeCvt(std::u8string_view str);
    }
}

#define RvLoggerDebugM(msg, ...) recurvis::Logger::debug(__func__, msg, __VA_ARGS__)

#endif //RECURVIS_LOGGER_H
