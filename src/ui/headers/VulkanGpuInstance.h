#ifndef RECURVIS_VULKANGPUINSTANCE_H
#define RECURVIS_VULKANGPUINSTANCE_H

#include "AbstractGpuInstance.h"

class GlfwApp;

struct VkInstance_T;

//TODO:remove
#include <vulkan/vulkan.h>
#include "Instance.h"

// TODO:remove
class VulkanGpuInstance;

class VulkanSurface;

class VulkanGpuInstance : public AbstractGpuInstance, public std::enable_shared_from_this<VulkanGpuInstance> {
public:
    // TODO:remove
    friend void
    testCode(const std::shared_ptr<VulkanGpuInstance> &instance, const std::shared_ptr<VulkanSurface> &surface);

    using VkInstanceInternalType = VkInstance_T *;

    struct Impl;

    // TODO:hide this implementation
    struct Impl {
        VulkanApiWrapper::Instance instance;

        explicit Impl(VulkanApiWrapper::Instance &&i) : instance(std::move(i)) {}
    };

private:
    std::unique_ptr<Impl> pimpl;

    std::vector<std::u8string> requestedExtensions;

    std::vector<std::u8string> requestedLayers;

protected:
    std::shared_ptr<Surface> createSurface(const std::shared_ptr<AbstractWindow> &window) override;

public:
    VulkanGpuInstance(const std::shared_ptr<GlfwApp> &app, const std::vector<std::u8string> &extensionRequest,
                      const std::vector<std::u8string> &layerRequest = {});

    ~VulkanGpuInstance() override;

    [[nodiscard]] const std::vector<std::u8string> &getRequestedExtensions() const;

    [[nodiscard]] const std::vector<std::u8string> &getRequestedLayers() const;

    [[nodiscard]] VkInstanceInternalType getHandler() const;
};


#endif //RECURVIS_VULKANGPUINSTANCE_H
