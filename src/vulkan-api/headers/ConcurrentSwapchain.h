#ifndef RECURVIS_CONCURRENTSWAPCHAIN_H
#define RECURVIS_CONCURRENTSWAPCHAIN_H

#include "SwapChain.h"

namespace VAW {
    class ConcurrentSwapchain : public SwapChain {
    public:
        ConcurrentSwapchain(const pLogicalDevice &logicalDevice,
                            VkSurfaceKHR surface,
                            VkImageUsageFlagBits usage,
                            std::optional<VkSwapchainKHR> old = std::nullopt);
    };
}

#endif //RECURVIS_CONCURRENTSWAPCHAIN_H
