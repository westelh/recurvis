#include <glfw_with_vulkan.h>
#include <spdlog/spdlog.h>
#include "VulkanGpuInstance.h"
#include "GlfwWindow.h"
#include "VulkanSurface.h"

namespace {
    VkSurfaceKHR create(const std::shared_ptr<VulkanGpuInstance> &instance, const std::shared_ptr<GlfwWindow> &window) {
        VkSurfaceKHR surface;
        auto result = glfwCreateWindowSurface(instance->getHandler(), window->getWindowHandle(), nullptr, &surface);
        if (result != VK_SUCCESS) {
            spdlog::critical("Surface creation failed!");
            throw std::runtime_error("Surface creation failed!");
        }
        return surface;
    }
}

struct VulkanSurface::Impl {
    VkSurfaceKHR handler;
};

VulkanSurface::VulkanSurface(const std::shared_ptr<VulkanGpuInstance> &instance,
                             const std::shared_ptr<GlfwWindow> &window)
        : Surface(window, instance),
          pimpl(std::make_unique<Impl>(Impl{create(instance, window)})) {

}

VulkanSurface::VulkanSurface(const VulkanSurface &origin) :
        Surface(origin.getWindow(), std::shared_ptr<AbstractGpuInstance>()),
        pimpl(std::make_unique<Impl>(Impl{origin.pimpl->handler})) {

}

VulkanSurface::~VulkanSurface() {
    spdlog::debug("Surface deleted");
    vkDestroySurfaceKHR(std::dynamic_pointer_cast<VulkanGpuInstance>(getInstance())->getHandler(), pimpl->handler,
                        nullptr);
}

VkSurfaceKHR_T *VulkanSurface::getHandler() const noexcept {
    return pimpl->handler;
}