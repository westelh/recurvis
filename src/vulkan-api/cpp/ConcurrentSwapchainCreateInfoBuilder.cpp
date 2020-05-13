#include "ConcurrentSwapchainCreateInfoBuilder.h"

using namespace VAW;

ConcurrentSwapchainCreateInfoBuilder::ConcurrentSwapchainCreateInfoBuilder(VkPhysicalDevice physicalDevice,
                                                                           VkSurfaceKHR surface,
                                                                           VkImageUsageFlags usageFlags,
                                                                           VkSwapchainKHR oldSwapchain)
        : DefaultSwapchainCreateInfoBuilder(physicalDevice, surface, usageFlags, oldSwapchain) {}

void ConcurrentSwapchainCreateInfoBuilder::setImageSharingMode() {
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
}

ConcurrentSwapchainCreateInfoBuilder::~ConcurrentSwapchainCreateInfoBuilder() = default;

void ConcurrentSwapchainCreateInfoBuilder::setQueueFamilyIndexCount() {
    createInfo.queueFamilyIndexCount = 0;
}

void ConcurrentSwapchainCreateInfoBuilder::setQueueFamilyIndices() {
    createInfo.pQueueFamilyIndices = nullptr;
}
