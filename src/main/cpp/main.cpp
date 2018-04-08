#include <iostream>
#include <chrono>
#include <thread>
#include "app.hpp"

int main(int argc, char** argv) {
    allegro_wrapper::app a;
    auto w = a.create_window(800, 600, []{
    });
    std::this_thread::sleep_for(std::chrono::seconds(10));
}
