#ifndef RECURVIS_VULKANSURFACE_H
#define RECURVIS_VULKANSURFACE_H

#include <memory>
#include "Surface.h"

class GlfwWindow;

class VulkanGpuInstance;

struct VkSurfaceKHR_T;

class VulkanSurface : public Surface {
    struct Impl;

    std::unique_ptr<Impl> pimpl;

public:
    VulkanSurface(const std::shared_ptr<VulkanGpuInstance> &instance, const std::shared_ptr<GlfwWindow> &window);

    VulkanSurface(const VulkanSurface &origin);

    ~VulkanSurface() override;

    [[nodiscard]] VkSurfaceKHR_T *getHandler() const noexcept;
};


#endif //RECURVIS_VULKANSURFACE_H
