#pragma once

#include <memory>
#include "window.hpp"

class app_interface {
private:

public:
    app_interface() = default;
    virtual ~app_interface() = default;
    virtual std::unique_ptr<window> create_window(int w, int h) = 0;
};