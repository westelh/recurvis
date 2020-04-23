#include <GLFW/glfw3.h>
#include "glfw_error.h"

using namespace std::string_literals;

glfw_error glfw_error::since_last_call() {
    const char* desc;
    int code = glfwGetError(&desc);
    return glfw_error(code, desc);
}

glfw_error::glfw_error(int c, std::string_view msg) : code(c), description{msg} {

}

int glfw_error::get_code() const {
    return code;
}

std::string_view glfw_error::get_description() const {
    return description;
}

const char *glfw_error::what() const noexcept {
    static char buf[128];
    std::strcpy(buf, to_string(*this).c_str());
    return buf;
}

std::string to_string(const glfw_error &e) {
    return "code:"s + std::to_string(e.get_code()) + " desc:"s + std::string{e.get_description()};
}
