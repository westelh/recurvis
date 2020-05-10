#ifndef RECURVIS_SWAPCHAIN_H
#define RECURVIS_SWAPCHAIN_H

#include <memory>
#include <vulkan/vulkan.h>
#include "PhysicalDevice.h"

// TODO: check if device has swapchain support

namespace VulkanApiWrapper {
    class LogicalDevice;

    class SwapChain {
    public:
        SwapChain(std::shared_ptr<LogicalDevice> logicalDevice, VkSwapchainCreateInfoKHR createInfo);

        SwapChain(const SwapChain &) = delete;

        SwapChain &operator=(const SwapChain &) = delete;

        SwapChain(SwapChain &&move) noexcept;

        SwapChain &operator=(SwapChain &&move) noexcept;

        virtual ~SwapChain();

    private:
        std::shared_ptr<LogicalDevice> logicalDevice;

        VkSwapchainKHR handler;
    };
}

#endif //RECURVIS_SWAPCHAIN_H
