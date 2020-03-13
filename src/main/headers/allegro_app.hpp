#ifndef INCLUDE_APP_HPP
#define INCLUDE_APP_HPP

#include <string>
#include <memory>
#include "app_interface.hpp"
#include "allegro_window.hpp"

class allegro_app : public app_interface {
public:
    allegro_app();
    virtual ~allegro_app();

    virtual std::unique_ptr<window> create_window(int w, int h) override;
};

#endif
