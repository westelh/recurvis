#pragma once

#include <thread>
#include <functional>
#include <atomic>

class window {
private:
    std::atomic_bool close_flag_m;
    std::thread update_thread_m;
protected:
    virtual void update() = 0;
public:
    window(int w, int h);
    virtual ~window();

    virtual void close() noexcept;
    virtual void close_and_wait() noexcept;
};