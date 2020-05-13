#ifndef RECURVIS_SWAPCHAIN_H
#define RECURVIS_SWAPCHAIN_H

#include <memory>
#include <vulkan/vulkan.h>
#include "PhysicalDevice.h"
#include "ImageView.h"

namespace VulkanApiWrapper {
    class LogicalDevice;

    class SwapchainCreateInfoBuilder;

    class SwapChain {
    public:
        using pLogicalDevice = std::shared_ptr<LogicalDevice>;
        using pInfoBuilder = std::unique_ptr<SwapchainCreateInfoBuilder>;

        SwapChain(pLogicalDevice logicalDevice, pInfoBuilder &&infoBuilder);

        SwapChain(const SwapChain &) = delete;

        SwapChain(SwapChain &&move) noexcept;

        SwapChain &operator=(const SwapChain &) = delete;

        SwapChain &operator=(SwapChain &&move) = delete;

        virtual ~SwapChain();

        [[nodiscard]] std::vector<VkImage> getSwapChainImages() const;

    private:
        pLogicalDevice logicalDevice;

        pInfoBuilder infoBuilder;

        VkSwapchainKHR handler;

        std::vector<VkImage> swapChainImages;

        std::vector<ImageView> imageViews;
    };
}

#endif //RECURVIS_SWAPCHAIN_H
