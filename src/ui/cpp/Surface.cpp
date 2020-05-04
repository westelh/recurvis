#include "Surface.h"

#include <utility>

Surface::Surface(const std::shared_ptr<AbstractWindow> &window_, const std::shared_ptr<AbstractGpuInstance> &instance)
        : window(window_),
          instance(instance) {

}

std::shared_ptr<AbstractWindow> Surface::getWindow() const {
    return window;
}

[[maybe_unused]] std::shared_ptr<AbstractGpuInstance> Surface::getInstance() const {
    return instance;
}
