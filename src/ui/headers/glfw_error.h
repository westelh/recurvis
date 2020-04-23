#ifndef RECURVIS_GLFW_ERROR_H
#define RECURVIS_GLFW_ERROR_H

#include <string>

class glfw_error : public std::exception {
    const int code;
    std::string description{};

public:
    static glfw_error since_last_call();

    glfw_error(int c, std::string_view msg);

    [[nodiscard]] int get_code() const;

    [[nodiscard]] std::string_view get_description() const;

    [[nodiscard]] const char *what() const noexcept override;
};

[[maybe_unused]] std::string to_string(const glfw_error& e);


#endif //RECURVIS_GLFW_ERROR_H
