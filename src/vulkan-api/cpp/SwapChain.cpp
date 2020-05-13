#include <utility>
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
        infoBuilder(std::move(infoBuilder_)),
        handler(nullptr),
        swapChainImages(),
        imageViews() {
    if (!infoBuilder) throw std::invalid_argument("info builder cannot be null!");
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
