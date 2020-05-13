#ifndef RECURVIS_CONCURRENTSWAPCHAINCREATEINFOBUILDER_H
#define RECURVIS_CONCURRENTSWAPCHAINCREATEINFOBUILDER_H

#include "DefaultSwapchainCreateInfoBuilder.h"

namespace VulkanApiWrapper {
    class ConcurrentSwapchainCreateInfoBuilder : public DefaultSwapchainCreateInfoBuilder {
    public:
        ConcurrentSwapchainCreateInfoBuilder(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
                                             VkImageUsageFlags flags, VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE);

        ~ConcurrentSwapchainCreateInfoBuilder() override;

        void setImageSharingMode() override;

        void setQueueFamilyIndexCount() override;

        void setQueueFamilyIndices() override;
    };
}

#endif //RECURVIS_CONCURRENTSWAPCHAINCREATEINFOBUILDER_H
