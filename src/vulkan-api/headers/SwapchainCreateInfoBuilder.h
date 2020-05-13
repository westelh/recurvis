#ifndef RECURVIS_SWAPCHAINCREATEINFOBUILDER_H
#define RECURVIS_SWAPCHAINCREATEINFOBUILDER_H

#include <vulkan/vulkan.h>

namespace VAW {
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

        [[nodiscard]] uint32_t getMinImageCount() const noexcept;

        [[nodiscard]] VkFormat getFormat() const noexcept;

        [[nodiscard]] VkColorSpaceKHR getColorSpace() const noexcept;

        [[nodiscard]] VkExtent2D getExtent() const noexcept;

        [[nodiscard]] uint32_t getArrayLayers() const noexcept;

        [[nodiscard]] VkImageUsageFlags getImageUsage() const noexcept;

        [[nodiscard]] VkSharingMode getImageSharingMode() const noexcept;

        [[nodiscard]] uint32_t getQueueFamilyIndexCount() const noexcept;

        [[nodiscard]] const uint32_t *getQueueFamilyIndices() const noexcept;

        [[nodiscard]] VkSurfaceTransformFlagBitsKHR getPreTransform() const noexcept;

        [[nodiscard]] VkCompositeAlphaFlagsKHR getCompositeAlpha() const noexcept;

        [[nodiscard]] VkPresentModeKHR getPresentMode() const noexcept;

        [[nodiscard]] VkBool32 isClipped() const noexcept;

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
