#pragma once

#include <memory>
#include <vector>
#include <list>
#include "spdlog/spdlog.h"
#include "window_interface.hpp"

class app_interface {
private:
    window_interface::window_updater updater;

    std::list<std::unique_ptr<window_interface>> windows;

protected:
    bool should_exit_loop() {
        return windows.empty();
    }

    int update_all_windows() {
        std::for_each(windows.begin(), windows.end(), [this](std::unique_ptr<window_interface> &w) {
            updater.update(w);
        });
        return windows.size();
    }

    // Remove from list and destroy windows
    std::size_t remove_closing_windows() {
        auto size_before = windows.size();
        windows.remove_if([](const std::unique_ptr<window_interface> &w) {
            return w->is_closing();
        });
        auto removed = size_before - windows.size();
        if (removed > 0) {
            spdlog::info("{} window was removed", removed);
        }
        return removed;
    }

    virtual std::unique_ptr<window_interface> create_window(int w, int h) = 0;

public:
    app_interface() : updater(), windows() {
    }

    virtual ~app_interface() = default;

    void add_window(int w, int h) {
        windows.push_back(create_window(w, h));
    }

    [[nodiscard]] window_interface::window_updater &getUpdater() {
        return updater;
    }

    virtual void main_loop() = 0;
};