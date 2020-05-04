#ifndef RECURVIS_SURFACE_H
#define RECURVIS_SURFACE_H

#include <memory>

class AbstractWindow;

class AbstractGpuInstance;

class Surface {
    std::shared_ptr<AbstractWindow> window;

    std::shared_ptr<AbstractGpuInstance> instance;

public:
    Surface(const std::shared_ptr<AbstractWindow> &window_, const std::shared_ptr<AbstractGpuInstance> &instance);

    virtual ~Surface() = default;

    [[nodiscard]] std::shared_ptr<AbstractWindow> getWindow() const;

    [[nodiscard]] std::shared_ptr<AbstractGpuInstance> getInstance() const;
};


#endif //RECURVIS_SURFACE_H
