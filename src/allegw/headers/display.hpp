#pragma once

namespace allegw {
    class app;

    // display will appear soon after the instantiation.
    class display {
        // only allows app class to create an instance.
        friend class app;
        // display handle returned by allegro system.
        ALLEGRO_DISPLAY* display_ptr;
        display();
    public:
        static constexpr int width = 800;
        static constexpr int height = 600;
        void wait_and_draw() noexcept;
        ~display();
    };
}
