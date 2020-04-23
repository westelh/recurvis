#pragma once

#include <thread>
#include <functional>
#include <atomic>

/*
/////////////////////
    window class
/////////////////////
    
*/
class window_interface {
public:
    // TODO:remove
    // request stopping update_thread_m
    void request_stop_update_thread() noexcept;


    // request stop and wait
    void stop_update_thread_and_wait() noexcept;

    // called window update loop
    virtual void update() = 0;

    // is the window requested for closing
    virtual bool is_closing() = 0;

    // resize
    [[maybe_unused]]
    [[nodiscard]] virtual bool resize(int w, int h) const = 0;

    window_interface(int w, int h);

    virtual ~window_interface();

    // close window immediately
    virtual void close() noexcept;

    // close window and wait until window update loop stops
    virtual void close_and_wait() noexcept;
};