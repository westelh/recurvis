#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include "app_interface.hpp"
#include "allegro_app.hpp"

int main(int argc, char** argv) {
    auto app = std::unique_ptr<app_interface>(new allegro_app{});

    std::vector<std::unique_ptr<window>> windows;

    auto window = app->create_window(800, 600);

    std::this_thread::sleep_for(std::chrono::seconds(10));
}
