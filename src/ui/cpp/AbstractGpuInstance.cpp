#include "AbstractGpuInstance.h"

std::shared_ptr<Surface> AbstractGpuInstance::getSurface(const std::shared_ptr<AbstractWindow> &window) {
    return createSurface(window);
}

AbstractGpuInstance::AbstractGpuInstance(std::shared_ptr<AbstractApp> app_) : app(app_) {

}

AbstractGpuInstance::~AbstractGpuInstance() = default;
