#ifndef RECURVIS_DEFAULTSWAPCHAINCREATEINFOBUILDER_H
#define RECURVIS_DEFAULTSWAPCHAINCREATEINFOBUILDER_H

#include <memory>
#include <vulkan/vulkan.h>
#include "PhysicalDevice.h"
#include "SwapchainCreateInfoBuilder.h"

namespace VulkanApiWrapper {
    class DefaultSwapchainCreateInfoBuilder : public SwapchainCreateInfoBuilder {
    public:
        DefaultSwapchainCreateInfoBuilder(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
                                          VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE);

        ~DefaultSwapchainCreateInfoBuilder() override = default;

        void setSurface() override;

        void setMinImageCount() override;

        void setFormat() override;

        void setColorSpace() override;

        void setExtent() override;

        void setArrayLayers() override;

        void setPreTransform() override;

        void setCompositeAlpha() override;

        void setPresentMode() override;

        void setClipped() override;

        void setOldSwapchain() override;

        VkSwapchainCreateInfoKHR build() override;

        [[nodiscard]] virtual VkSurfaceFormatKHR
        chooseFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) const;

        [[nodiscard]] virtual VkPresentModeKHR
        choosePresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes) const;

        [[nodiscard]] virtual VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) const;

    private:
        VkSurfaceKHR surface{};

        VkSwapchainKHR oldSwapchain{};

        VkSurfaceCapabilitiesKHR capabilities{};

        std::vector<VkSurfaceFormatKHR> availableFormats{};

        std::vector<VkPresentModeKHR> availablePresentModes{};
    };
}

#endif //RECURVIS_DEFAULTSWAPCHAINCREATEINFOBUILDER_H
