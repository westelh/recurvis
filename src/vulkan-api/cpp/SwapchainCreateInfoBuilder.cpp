#include "SwapchainCreateInfoBuilder.h"

uint32_t VAW::SwapchainCreateInfoBuilder::getMinImageCount() const noexcept {
    return createInfo.minImageCount;
}

VkFormat VAW::SwapchainCreateInfoBuilder::getFormat() const noexcept {
    return createInfo.imageFormat;
}

VkColorSpaceKHR VAW::SwapchainCreateInfoBuilder::getColorSpace() const noexcept {
    return createInfo.imageColorSpace;
}

VkExtent2D VAW::SwapchainCreateInfoBuilder::getExtent() const noexcept {
    return createInfo.imageExtent;
}

uint32_t VAW::SwapchainCreateInfoBuilder::getArrayLayers() const noexcept {
    return createInfo.imageArrayLayers;
}

VkImageUsageFlags VAW::SwapchainCreateInfoBuilder::getImageUsage() const noexcept {
    return createInfo.imageUsage;
}

VkSharingMode VAW::SwapchainCreateInfoBuilder::getImageSharingMode() const noexcept {
    return createInfo.imageSharingMode;
}

uint32_t VAW::SwapchainCreateInfoBuilder::getQueueFamilyIndexCount() const noexcept {
    return createInfo.queueFamilyIndexCount;
}

const uint32_t *VAW::SwapchainCreateInfoBuilder::getQueueFamilyIndices() const noexcept {
    return createInfo.pQueueFamilyIndices;
}

VkSurfaceTransformFlagBitsKHR VAW::SwapchainCreateInfoBuilder::getPreTransform() const noexcept {
    return createInfo.preTransform;
}

VkCompositeAlphaFlagsKHR VAW::SwapchainCreateInfoBuilder::getCompositeAlpha() const noexcept {
    return createInfo.compositeAlpha;
}

VkPresentModeKHR VAW::SwapchainCreateInfoBuilder::getPresentMode() const noexcept {
    return createInfo.presentMode;
}

VkBool32 VAW::SwapchainCreateInfoBuilder::isClipped() const noexcept {
    return createInfo.clipped;
}
