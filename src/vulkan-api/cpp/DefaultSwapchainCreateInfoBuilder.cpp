#include "DefaultSwapchainCreateInfoBuilder.h"
#include "VulkanError.h"

using namespace VulkanApiWrapper;

namespace {
    inline VkSurfaceCapabilitiesKHR queryCapabilities(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        VkSurfaceCapabilitiesKHR ret;
        if (auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &ret); result !=
                                                                                                    VK_SUCCESS) {
            throw VulkanError(result);
        }
        return ret;
    }

    inline uint32_t countFormats(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        uint32_t ret;
        if (auto result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &ret, nullptr); result !=
                                                                                                        VK_SUCCESS) {
            throw VulkanError(result);
        }
        return ret;
    }

    inline std::vector<VkSurfaceFormatKHR> queryFormats(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        std::vector<VkSurfaceFormatKHR> ret(countFormats(physicalDevice, surface));
        uint32_t count;
        if (auto result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, ret.data()); result !=
                                                                                                             VK_SUCCESS) {
            throw VulkanError(result);
        }
        return ret;
    }

    inline uint32_t countPresentModes(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        uint32_t ret;
        if (auto result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &ret, nullptr); result !=
                                                                                                             VK_SUCCESS) {
            throw VulkanError(result);
        }
        return ret;
    }

    inline std::vector<VkPresentModeKHR> queryPresentModes(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        std::vector<VkPresentModeKHR> ret(countPresentModes(physicalDevice, surface));
        uint32_t count;
        if (auto result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, ret.data());
                result != VK_SUCCESS) {
            throw VulkanError(result);
        }
        return ret;
    }
}

DefaultSwapchainCreateInfoBuilder::DefaultSwapchainCreateInfoBuilder(VkPhysicalDevice physicalDevice,
                                                                     VkSurfaceKHR surface, VkImageUsageFlags flags_,
                                                                     VkSwapchainKHR oldSwapchain_)
        :
        surface(surface),
        flags(flags_),
        oldSwapchain(oldSwapchain_),
        capabilities(queryCapabilities(physicalDevice, surface)),
        availableFormats(queryFormats(physicalDevice, surface)),
        availablePresentModes(queryPresentModes(physicalDevice, surface)) {

}

void DefaultSwapchainCreateInfoBuilder::setSurface() {
    createInfo.surface = this->surface;
}

void DefaultSwapchainCreateInfoBuilder::setMinImageCount() {
    createInfo.minImageCount = this->capabilities.minImageCount + 1;
}

void DefaultSwapchainCreateInfoBuilder::setFormat() {
    createInfo.imageFormat = chooseFormat(this->availableFormats).format;
}

void DefaultSwapchainCreateInfoBuilder::setColorSpace() {
    createInfo.imageColorSpace = chooseFormat(this->availableFormats).colorSpace;
}

void DefaultSwapchainCreateInfoBuilder::setExtent() {
    createInfo.imageExtent = chooseSwapExtent(this->capabilities);
}

void DefaultSwapchainCreateInfoBuilder::setArrayLayers() {
    // Always 1 unless application implements stereoscopic 3D
    createInfo.imageArrayLayers = 1;
}

void DefaultSwapchainCreateInfoBuilder::setPreTransform() {
    createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
}

void DefaultSwapchainCreateInfoBuilder::setCompositeAlpha() {
    // Ignore
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
}

void DefaultSwapchainCreateInfoBuilder::setPresentMode() {
    createInfo.presentMode = choosePresentMode(availablePresentModes);
}

void DefaultSwapchainCreateInfoBuilder::setClipped() {
    createInfo.clipped = VK_TRUE;
}

void DefaultSwapchainCreateInfoBuilder::setOldSwapchain() {
    createInfo.oldSwapchain = this->oldSwapchain;
}

VkSwapchainCreateInfoKHR DefaultSwapchainCreateInfoBuilder::build() {
    return VkSwapchainCreateInfoKHR();
}

VkSurfaceFormatKHR
DefaultSwapchainCreateInfoBuilder::chooseFormat(const std::vector<VkSurfaceFormatKHR> &formatsAvailable) const {
    for (const auto &availableFormat : formatsAvailable) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }
    throw std::runtime_error("No available format!");
}

VkPresentModeKHR
DefaultSwapchainCreateInfoBuilder::choosePresentMode(
        [[maybe_unused]] const std::vector<VkPresentModeKHR> &presentModesAvailable) const {
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D DefaultSwapchainCreateInfoBuilder::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilitiesKhr) const {
    if (capabilitiesKhr.currentExtent.width != UINT32_MAX) {
        return capabilitiesKhr.currentExtent;
    } else {
        VkExtent2D actualExtent = {400, 200};

        actualExtent.width = std::max(capabilitiesKhr.minImageExtent.width,
                                      std::min(capabilitiesKhr.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilitiesKhr.minImageExtent.height,
                                       std::min(capabilitiesKhr.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

void DefaultSwapchainCreateInfoBuilder::setImageUsage() {
    createInfo.imageUsage = this->flags;
}



