#ifndef RECURVIS_ABSTRACTGPUINSTANCE_H
#define RECURVIS_ABSTRACTGPUINSTANCE_H

#include <memory>
#include <vector>

class AbstractApp;

class Surface;

class AbstractWindow;

class AbstractGpuInstance {
    std::shared_ptr<AbstractApp> app;

protected:
    virtual std::shared_ptr<Surface> createSurface(const std::shared_ptr<AbstractWindow> &window) = 0;

public:
    explicit AbstractGpuInstance(std::shared_ptr<AbstractApp> app);

    virtual ~AbstractGpuInstance();

    std::shared_ptr<Surface> getSurface(const std::shared_ptr<AbstractWindow> &window);
};


#endif //RECURVIS_ABSTRACTGPUINSTANCE_H
