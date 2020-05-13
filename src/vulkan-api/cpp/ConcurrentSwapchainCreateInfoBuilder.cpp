#include "ConcurrentSwapchainCreateInfoBuilder.h"

using namespace VulkanApiWrapper;

ConcurrentSwapchainCreateInfoBuilder::ConcurrentSwapchainCreateInfoBuilder(VkPhysicalDevice physicalDevice,
                                                                           VkSurfaceKHR surface,
                                                                           VkImageUsageFlags flags,
                                                                           VkSwapchainKHR oldSwapchain)
        : DefaultSwapchainCreateInfoBuilder(physicalDevice, surface, flags, oldSwapchain) {}

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
