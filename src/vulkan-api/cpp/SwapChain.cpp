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

    // TODO: check if device supports VK_swapchain
    bool validateDevice(const LogicalDevice &device) noexcept {
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
