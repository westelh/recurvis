#include <optional>
#include "ConcurrentSwapchain.h"
#include "ConcurrentSwapchainCreateInfoBuilder.h"
#include "LogicalDevice.h"

using namespace VAW;

namespace {
    using pBuilder = std::unique_ptr<VAW::SwapchainCreateInfoBuilder>;

    pBuilder
    makeBuilder(VkPhysicalDevice device, VkSurfaceKHR surface, VkImageUsageFlagBits usage, VkSwapchainKHR old) {
        return pBuilder(new ConcurrentSwapchainCreateInfoBuilder(device, surface, usage, old));
    }
}

ConcurrentSwapchain::ConcurrentSwapchain(const pLogicalDevice &logicalDevice,
                                         VkSurfaceKHR surface,
                                         VkImageUsageFlagBits usage,
                                         std::optional<VkSwapchainKHR> old) :
        SwapChain(logicalDevice,
                  makeBuilder(logicalDevice->getPhysicalDevice().getDeviceHandle(), surface, usage, old.value_or(
                          reinterpret_cast<VkSwapchainKHR_T *>(VK_NULL_HANDLE)))) {

}
