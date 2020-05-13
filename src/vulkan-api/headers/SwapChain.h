#ifndef RECURVIS_SWAPCHAIN_H
#define RECURVIS_SWAPCHAIN_H

#include <memory>
#include <vulkan/vulkan.h>
#include "PhysicalDevice.h"
#include "ImageView.h"

namespace VAW {
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

        [[nodiscard]] uint32_t getMinImageCount() const noexcept;

        [[nodiscard]] VkFormat getFormat() const noexcept;

        [[nodiscard]] VkColorSpaceKHR getColorSpace() const noexcept;

        [[nodiscard]] VkExtent2D getExtent() const noexcept;

        [[nodiscard]] VkImageUsageFlags getUsageFlags() const noexcept;

        [[nodiscard]] VkSharingMode getSharingMode() const noexcept;

        [[nodiscard]] std::vector<uint32_t> getQueueFamilyIndices() const noexcept;

        [[nodiscard]] VkSurfaceTransformFlagBitsKHR getPreTransform() const noexcept;

        [[nodiscard]] VkCompositeAlphaFlagsKHR getCompositeAlpha() const noexcept;

        [[nodiscard]] VkPresentModeKHR getPresentMode() const noexcept;

        [[nodiscard]] VkBool32 isClipped() const noexcept;

        [[nodiscard]] std::vector<VkImage> getSwapChainImages() const;

        VkSwapchainKHR getHandler() const;

    private:
        pLogicalDevice logicalDevice;

        uint32_t minImageCount;

        VkFormat format;

        VkColorSpaceKHR colorSpace;

        VkExtent2D extent;

        VkImageUsageFlags usageFlags;

        VkSharingMode sharingMode;

        uint32_t queueFamilyIndicesCount;

        const uint32_t *pQueueFamilyIndices;

        VkSurfaceTransformFlagBitsKHR preTransform;

        VkCompositeAlphaFlagsKHR compositeAlpha;

        VkPresentModeKHR presentMode;

        VkBool32 clipped;

        VkSwapchainKHR handler;

        std::vector<VkImage> swapChainImages;

        std::vector<ImageView> imageViews;
    };
}

#endif //RECURVIS_SWAPCHAIN_H
