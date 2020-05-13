#include <optional>
#include "ConcurrentSwapchain.h"
#include "ConcurrentSwapchainCreateInfoBuilder.h"
#include "LogicalDevice.h"

using namespace VAW;

namespace {
    using pBuilder = std::unique_ptr<VAW::SwapchainCreateInfoBuilder>;

    pBuilder
    makeBuilder(VkPhysicalDevice device, VkSurfaceKHR surface, VkImageUsageFlagBits usage,
                std::optional<VkSwapchainKHR> old) {
        if (old.has_value()) {
            return pBuilder(new ConcurrentSwapchainCreateInfoBuilder(device, surface, usage, old.value()));
        } else {
            return pBuilder(new ConcurrentSwapchainCreateInfoBuilder(device, surface, usage));
        }
    }
}

ConcurrentSwapchain::ConcurrentSwapchain(const pLogicalDevice &logicalDevice,
                                         VkSurfaceKHR surface,
                                         VkImageUsageFlagBits usage,
                                         std::optional<VkSwapchainKHR> old) :
        SwapChain(logicalDevice,
                  makeBuilder(logicalDevice->getPhysicalDevice().getDeviceHandle(), surface, usage, old)) {

}
