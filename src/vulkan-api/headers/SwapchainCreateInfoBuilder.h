#ifndef RECURVIS_SWAPCHAINCREATEINFOBUILDER_H
#define RECURVIS_SWAPCHAINCREATEINFOBUILDER_H

#include <vulkan/vulkan.h>

namespace VulkanApiWrapper {
    class SwapchainCreateInfoBuilder {
    public:
        virtual void setSurface() = 0;

        virtual void setMinImageCount() = 0;

        virtual void setFormat() = 0;

        virtual void setColorSpace() = 0;

        virtual void setExtent() = 0;

        virtual void setArrayLayers() = 0;

        virtual void setImageUsage() = 0;

        virtual void setImageSharingMode() = 0;

        virtual void setQueueFamilyIndexCount() = 0;

        virtual void setQueueFamilyIndices() = 0;

        virtual void setPreTransform() = 0;

        virtual void setCompositeAlpha() = 0;

        virtual void setPresentMode() = 0;

        virtual void setClipped() = 0;

        virtual void setOldSwapchain() = 0;

        virtual VkSwapchainCreateInfoKHR build() = 0;

        SwapchainCreateInfoBuilder() {
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.pNext = nullptr;
            createInfo.flags = 0;
        }

        virtual ~SwapchainCreateInfoBuilder() = default;

    protected:
        VkSwapchainCreateInfoKHR createInfo{};
    };
}

#endif //RECURVIS_SWAPCHAINCREATEINFOBUILDER_H
