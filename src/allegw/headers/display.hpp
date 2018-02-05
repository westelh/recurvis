#pragma once

#include <memory>
#include <mutex>

namespace allegw {
    class app;
    class timeout;
    class event;
    class event_queue;

    // display will appear soon after the instantiation.
    class display {
    public:
        static constexpr int width = 800;
        static constexpr int height = 600;
        void wait_and_draw() const noexcept;
        bool is_time_to_close() const noexcept; 
        ~display() noexcept;
    private:
        // only allows app class to create an instance.
        friend class app;
        // thread safe
        mutable std::recursive_mutex mutex;
        inline const std::unique_lock<std::recursive_mutex> get_lock() const noexcept;
        // deleter for display_ptr.
        struct deleter {
            void operator()(ALLEGRO_DISPLAY* disp) const;
        };
        // display handle returned by allegro system.
        std::unique_ptr<ALLEGRO_DISPLAY, deleter> display_ptr;
        // event queue.
        ALLEGRO_EVENT_QUEUE* events; 
        ALLEGRO_TIMEOUT* timeout;
        display();
    };
}
