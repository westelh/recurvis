#pragma once

#include <thread>
#include <functional>
#include <atomic>

/*
/////////////////////
    window class
/////////////////////

 todo: rearrange visibility
    
*/
class window_interface {
protected:
    virtual void update() = 0;

public:
    static constexpr int refresh_rate = 60;
    static constexpr std::chrono::milliseconds wait = std::chrono::milliseconds(1000 / refresh_rate);

    window_interface(int w, int h);

    virtual ~window_interface() = default;

    // is the window requested for closing
    virtual bool is_closing() = 0;

    // close window immediately
    virtual void close() noexcept = 0;

    // resize
    [[maybe_unused]]
    [[nodiscard]] virtual bool resize(int w, int h) const = 0;

    class window_updater {
    public:
        window_updater() = default;

        ~window_updater() = default;

        void update(std::unique_ptr<window_interface> &window);
    };
};