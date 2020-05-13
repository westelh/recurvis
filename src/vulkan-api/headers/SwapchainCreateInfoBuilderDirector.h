#ifndef RECURVIS_SWAPCHAINCREATEINFOBUILDERDIRECTOR_H
#define RECURVIS_SWAPCHAINCREATEINFOBUILDERDIRECTOR_H

#include <memory>
#include <vulkan/vulkan.h>

namespace VulkanApiWrapper {
    class SwapchainCreateInfoBuilder;

    class SwapchainCreateInfoBuilderDirector final {
    public:
        explicit SwapchainCreateInfoBuilderDirector(std::unique_ptr<SwapchainCreateInfoBuilder> builder);

        ~SwapchainCreateInfoBuilderDirector();

        VkSwapchainCreateInfoKHR construct();

    private:
        std::unique_ptr<SwapchainCreateInfoBuilder> builder;
    };
}

#endif //RECURVIS_SWAPCHAINCREATEINFOBUILDERDIRECTOR_H
