#include "glfw_with_vulkan.h"
#include "GlfwApp.h"
#include "VulkanSurface.h"
#include "VulkanGpuInstance.h"
#include "Instance.h"
#include "InstanceBuilderDebug.h"
#include "InstanceBuilderDirector.h"
#include "AppGpuInstanceBuilder.h"

// TODO:put implementation of Impl here

using namespace VulkanApiWrapper;

namespace {
    std::unique_ptr<VulkanGpuInstance::Impl>
    genImpl(const std::shared_ptr<AbstractApp> &app, const std::vector<std::u8string> &extensionRequest,
            const std::vector<std::u8string> &layerRequest) {
        InstanceBuilderDirector director(
                makeDebugBuilderFrom(std::make_unique<AppGpuInstanceBuilder>(app, layerRequest, extensionRequest)));
        return std::make_unique<VulkanGpuInstance::Impl>(director.construct());
    }
}

std::shared_ptr<Surface> VulkanGpuInstance::createSurface(const std::shared_ptr<AbstractWindow> &window) {
    return std::shared_ptr<Surface>(
            new VulkanSurface(shared_from_this(), std::dynamic_pointer_cast<GlfwWindow>(window)));
}

VulkanGpuInstance::VulkanGpuInstance(const std::shared_ptr<GlfwApp> &app,
                                     const std::vector<std::u8string> &extensionRequest,
                                     const std::vector<std::u8string> &layerRequest)
        : AbstractGpuInstance(std::dynamic_pointer_cast<AbstractApp>(app)),
          pimpl(genImpl(std::dynamic_pointer_cast<AbstractApp>(app), extensionRequest, layerRequest)),
          requestedExtensions(extensionRequest),
          requestedLayers(layerRequest) {

}

VulkanGpuInstance::~VulkanGpuInstance() = default;

VulkanGpuInstance::VkInstanceInternalType VulkanGpuInstance::getHandler() const {
    return VulkanGpuInstance::pimpl->instance.getHandler();
}

const std::vector<std::u8string> &VulkanGpuInstance::getRequestedExtensions() const {
    return requestedExtensions;
}

const std::vector<std::u8string> &VulkanGpuInstance::getRequestedLayers() const {
    return requestedLayers;
}
