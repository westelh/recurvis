#include <utility>
#include <algorithm>
#include "SwapChain.h"
#include "VulkanError.h"
#include "SwapchainCreateInfoBuilder.h"
#include "SwapchainCreateInfoBuilderDirector.h"
#include "LogicalDevice.h"

using namespace VulkanApiWrapper;

namespace {
    // TODO: implement validateCreateInfo()
    bool validateCreateInfo(const VkSwapchainCreateInfoKHR &createInfo) noexcept {
        return createInfo.sType == VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    }

    bool validateDevice(const LogicalDevice &device) noexcept {
        return device.checkIfExtensionEnabled(u8"VK_KHR_swapchain");
    }

    uint32_t countSwapChainImages(VkDevice device, VkSwapchainKHR swapchain) {
        uint32_t ret;
        if (auto result = vkGetSwapchainImagesKHR(device, swapchain, &ret, nullptr); result != VK_SUCCESS) {
            throw VulkanError(result);
        }
        return ret;
    }

    std::vector<VkImage> querySwapChainImages(VkDevice device, VkSwapchainKHR swapchain) {
        uint32_t size = countSwapChainImages(device, swapchain);
        std::vector<VkImage> ret(size);
        if (auto result = vkGetSwapchainImagesKHR(device, swapchain, &size, ret.data()); result != VK_SUCCESS) {
            throw VulkanError(result);
        }
        return ret;
    }
}

SwapChain::SwapChain(pLogicalDevice logicalDevice_, pInfoBuilder &&infoBuilder_) :
        logicalDevice(std::move(logicalDevice_)),
        minImageCount(infoBuilder_ ? infoBuilder_->getMinImageCount() : 0),
        format(infoBuilder_ ? infoBuilder_->getFormat() : VkFormat{}),
        colorSpace(infoBuilder_ ? infoBuilder_->getColorSpace() : VkColorSpaceKHR{}),
        extent(infoBuilder_ ? infoBuilder_->getExtent() : VkExtent2D{}),
        usageFlags(infoBuilder_ ? infoBuilder_->getImageUsage() : VkImageUsageFlagBits{}),
        sharingMode(infoBuilder_ ? infoBuilder_->getImageSharingMode() : VkSharingMode{}),
        queueFamilyIndicesCount(infoBuilder_ ? infoBuilder_->getQueueFamilyIndexCount() : 0),
        pQueueFamilyIndices(infoBuilder_ ? infoBuilder_->getQueueFamilyIndices() : nullptr),
        preTransform(infoBuilder_ ? infoBuilder_->getPreTransform() : VkSurfaceTransformFlagBitsKHR{}),
        compositeAlpha(infoBuilder_ ? infoBuilder_->getCompositeAlpha() : VkCompositeAlphaFlagBitsKHR{}),
        presentMode(infoBuilder_ ? infoBuilder_->getPresentMode() : VkPresentModeKHR{}),
        clipped(infoBuilder_ ? infoBuilder_->isClipped() : VK_FALSE),
        handler(nullptr),
        swapChainImages(),
        imageViews() {
    if (!infoBuilder_) throw std::invalid_argument("info builder cannot be null!");

    if (!logicalDevice) throw std::invalid_argument("Logical device cannot be null!");
    if (!validateDevice(*logicalDevice)) throw std::invalid_argument("Invalid device!");
    auto info = SwapchainCreateInfoBuilderDirector{std::move(infoBuilder_)}.construct();
    if (!validateCreateInfo(info)) throw std::logic_error("Invalid swapchain create info!");
    if (auto result = vkCreateSwapchainKHR(logicalDevice->getHandler(), &info, nullptr, &handler); result != VK_SUCCESS)
        throw VulkanError(result);
    swapChainImages = querySwapChainImages(logicalDevice->getHandler(), this->handler);
}

SwapChain::~SwapChain() {
    if (handler != nullptr) {
        vkDestroySwapchainKHR(logicalDevice->getHandler(), handler, nullptr);
    }
}

SwapChain::SwapChain(SwapChain &&move) noexcept:
        logicalDevice(std::move(move.logicalDevice)),
        handler(move.handler) {
    move.handler = nullptr;
}

std::vector<VkImage> SwapChain::getSwapChainImages() const {
    return swapChainImages;
}

uint32_t SwapChain::getMinImageCount() const noexcept {
    return minImageCount;
}

VkFormat SwapChain::getFormat() const noexcept {
    return format;
}

VkColorSpaceKHR SwapChain::getColorSpace() const noexcept {
    return colorSpace;
}

VkExtent2D SwapChain::getExtent() const noexcept {
    return extent;
}

VkImageUsageFlags SwapChain::getUsageFlags() const noexcept {
    return usageFlags;
}

VkSharingMode SwapChain::getSharingMode() const noexcept {
    return sharingMode;
}

std::vector<uint32_t> SwapChain::getQueueFamilyIndices() const noexcept {
    std::vector<uint32_t> ret(queueFamilyIndicesCount);
    auto indices = pQueueFamilyIndices;
    std::copy(indices, indices + queueFamilyIndicesCount, ret.begin());
    return ret;
}

VkSurfaceTransformFlagBitsKHR SwapChain::getPreTransform() const noexcept {
    return preTransform;
}

VkCompositeAlphaFlagsKHR SwapChain::getCompositeAlpha() const noexcept {
    return compositeAlpha;
}

VkPresentModeKHR SwapChain::getPresentMode() const noexcept {
    return presentMode;
}

VkBool32 SwapChain::isClipped() const noexcept {
    return clipped;
}
