#include "SwapchainCreateInfoBuilder.h"

uint32_t VulkanApiWrapper::SwapchainCreateInfoBuilder::getMinImageCount() const noexcept {
    return createInfo.minImageCount;
}

VkFormat VulkanApiWrapper::SwapchainCreateInfoBuilder::getFormat() const noexcept {
    return createInfo.imageFormat;
}

VkColorSpaceKHR VulkanApiWrapper::SwapchainCreateInfoBuilder::getColorSpace() const noexcept {
    return createInfo.imageColorSpace;
}

VkExtent2D VulkanApiWrapper::SwapchainCreateInfoBuilder::getExtent() const noexcept {
    return createInfo.imageExtent;
}

uint32_t VulkanApiWrapper::SwapchainCreateInfoBuilder::getArrayLayers() const noexcept {
    return createInfo.imageArrayLayers;
}

VkImageUsageFlags VulkanApiWrapper::SwapchainCreateInfoBuilder::getImageUsage() const noexcept {
    return createInfo.imageUsage;
}

VkSharingMode VulkanApiWrapper::SwapchainCreateInfoBuilder::getImageSharingMode() const noexcept {
    return createInfo.imageSharingMode;
}

uint32_t VulkanApiWrapper::SwapchainCreateInfoBuilder::getQueueFamilyIndexCount() const noexcept {
    return createInfo.queueFamilyIndexCount;
}

const uint32_t *VulkanApiWrapper::SwapchainCreateInfoBuilder::getQueueFamilyIndices() const noexcept {
    return createInfo.pQueueFamilyIndices;
}

VkSurfaceTransformFlagBitsKHR VulkanApiWrapper::SwapchainCreateInfoBuilder::getPreTransform() const noexcept {
    return createInfo.preTransform;
}

VkCompositeAlphaFlagsKHR VulkanApiWrapper::SwapchainCreateInfoBuilder::getCompositeAlpha() const noexcept {
    return createInfo.compositeAlpha;
}

VkPresentModeKHR VulkanApiWrapper::SwapchainCreateInfoBuilder::getPresentMode() const noexcept {
    return createInfo.presentMode;
}

VkBool32 VulkanApiWrapper::SwapchainCreateInfoBuilder::isClipped() const noexcept {
    return createInfo.clipped;
}
