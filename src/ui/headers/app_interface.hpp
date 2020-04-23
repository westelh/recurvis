#pragma once

#include <memory>
#include <vector>
#include "window_interface.hpp"

class app_interface {
public:
    app_interface() = default;

    virtual ~app_interface() = default;

    [[nodiscard]] virtual std::shared_ptr<window_interface> create_window(int w, int h) = 0;
};