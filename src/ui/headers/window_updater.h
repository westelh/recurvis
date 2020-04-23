#ifndef RECURVIS_WINDOW_UPDATER_H
#define RECURVIS_WINDOW_UPDATER_H

#include <memory>
#include <thread>
#include <atomic>
#include <list>
#include "window_interface.hpp"

class window_updater {
    static constexpr int refresh_rate = 60;
    static constexpr std::chrono::milliseconds wait = std::chrono::milliseconds(1000 / refresh_rate);

    std::list<std::shared_ptr<window_interface>> windows;

    std::atomic_flag loop_continue;
protected:
    void updater();

public:
    explicit window_updater(const std::shared_ptr<window_interface> &window);

    ~window_updater();

    void loop() {
        updater();
    }
};


#endif //RECURVIS_WINDOW_UPDATER_H
