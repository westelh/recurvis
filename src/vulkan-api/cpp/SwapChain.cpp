#include <utility>
#include "SwapChain.h"
#include "VulkanError.h"
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

SwapChain::SwapChain(std::shared_ptr<LogicalDevice> logicalDevice_, VkSwapchainCreateInfoKHR createInfo) :
        logicalDevice(std::move(logicalDevice_)),
        handler(nullptr) {
    if (!logicalDevice) throw std::invalid_argument("Logical device cannot be null!");
    if (!validateDevice(*logicalDevice)) throw std::invalid_argument("Invalid device!");
    if (!validateCreateInfo(createInfo)) throw std::invalid_argument("Invalid create info!");
    if (auto result = vkCreateSwapchainKHR(logicalDevice->getHandler(), &createInfo, nullptr, &handler); result !=
                                                                                                         VK_SUCCESS) {
        throw VulkanError(result);
    }
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

SwapChain &SwapChain::operator=(SwapChain &&move) noexcept {
    this->logicalDevice = std::move(move.logicalDevice);
    this->handler = move.handler;
    move.handler = nullptr;
    return *this;
}

std::vector<VkImage> SwapChain::getSwapChainImages() const {
    return swapChainImages;
}
