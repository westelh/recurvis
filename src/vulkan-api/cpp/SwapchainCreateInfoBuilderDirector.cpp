#include "SwapchainCreateInfoBuilderDirector.h"
#include "SwapchainCreateInfoBuilder.h"

using namespace VulkanApiWrapper;

SwapchainCreateInfoBuilderDirector::SwapchainCreateInfoBuilderDirector(
        std::unique_ptr<SwapchainCreateInfoBuilder> builder_) :
        builder(std::move(builder_)) {
    if (!builder) throw std::invalid_argument("builder cannot be null!");
}

SwapchainCreateInfoBuilderDirector::~SwapchainCreateInfoBuilderDirector() = default;

VkSwapchainCreateInfoKHR SwapchainCreateInfoBuilderDirector::construct() {
    builder->setSurface();
    builder->setMinImageCount();
    builder->setFormat();
    builder->setColorSpace();
    builder->setExtent();
    builder->setArrayLayers();
    builder->setImageUsage();
    builder->setImageSharingMode();
    builder->setQueueFamilyIndexCount();
    builder->setQueueFamilyIndices();
    builder->setPreTransform();
    builder->setCompositeAlpha();
    builder->setPresentMode();
    builder->setClipped();
    builder->setOldSwapchain();
    return builder->build();
}
