#pragma once

#include <thread>
#include <functional>
#include <atomic>

/*
/////////////////////
    window class
/////////////////////
    
*/
class window {
private:
    std::atomic_bool close_flag_m;
    std::thread update_thread_m;
protected:
    // called window update loop
    virtual void update() = 0;

public:
    window(int w, int h);
    virtual ~window();

    // close window immediately
    virtual void close() noexcept;

    // close window and wait until window update loop stops
    virtual void close_and_wait() noexcept;
};