#include <internal/VulkanSurface.h>
#include "Version.h"
#include "spdlog/spdlog.h"
#include "util.h"
#include "API_Implement.h"
#include "VulkanGpuInstance.h"
#include "GlfwApp.h"

#include <set>
#include <vulkan/vulkan.h>
#include <LogicalDevice.h>
#include <VulkanError.h>
#include "PhysicalDevice.h"
#include "ConcurrentSwapchainCreateInfoBuilder.h"
#include "Instance.h"
#include "SwapChain.h"

// TODO:Rename VulkanApiWrapper to VAW

void testCode(const std::shared_ptr<VulkanGpuInstance> &instance, const std::shared_ptr<VulkanSurface> &surface);

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) {
    spdlog::set_level(spdlog::level::debug);
    auto appVersion = Version(0, 0, 0);
    auto app = getVulkanApp("recurvis", appVersion);
    auto window = app->add_window(200, 150);

    auto layerRequest = VulkanApiWrapper::Instance::enumerateAvailableLayerNames();
    std::erase(layerRequest, u8"VK_LAYER_LUNARG_api_dump");
    auto extensionRequest = VulkanApiWrapper::Instance::enumerateAvailableInstanceExtensionNames();

    std::shared_ptr<AbstractGpuInstance> instance(
            new VulkanGpuInstance(std::dynamic_pointer_cast<GlfwApp>(app), extensionRequest, layerRequest));

    std::shared_ptr<Surface> surface = instance->getSurface(window);

    testCode(std::dynamic_pointer_cast<VulkanGpuInstance>(instance), std::dynamic_pointer_cast<VulkanSurface>(surface));

    app->main_loop();
}

void testCode(const std::shared_ptr<VulkanGpuInstance> &instance, const std::shared_ptr<VulkanSurface> &surface) {
    ////////////////////////////////////////////////////////////////////////
    // Platform specific operations for purpose of leaning vulkan
    // TODO: remove dependency

    [[maybe_unused]] auto surfaceHandler = surface->getHandler();
    [[maybe_unused]] auto instanceHandler = instance->getHandler();
    auto &internalInstance = (*instance).pimpl->instance;

    const auto &devices = VulkanApiWrapper::PhysicalDevice::availableDevices(internalInstance);
    const auto &targetDevice = devices.front();
    const auto &families = targetDevice.getSuitableQueueFamilies(VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT);

    for (std::size_t i = 0; i < families.value().size(); ++i) {
        VkBool32 reallySupportsSurface = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(
                (VkPhysicalDevice_T *) targetDevice.getDeviceHandle(),
                families.value().at(i).index,
                (VkSurfaceKHR_T *) surface->getHandler(),
                &reallySupportsSurface);
        spdlog::debug("Queue family {}/{} supports surface:{}", i, families.value().size(),
                      static_cast<bool>(reallySupportsSurface));
    }

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {0, 1};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures features{};
    std::vector<std::u8string> deviceExtensions{u8"VK_KHR_swapchain"};
    auto logicalDevice = std::make_shared<VulkanApiWrapper::LogicalDevice>(targetDevice, features, queueCreateInfos,
                                                                           deviceExtensions);

    [[maybe_unused]] const auto &queues = logicalDevice->getQueues();

    VulkanApiWrapper::SwapChain swapChain(logicalDevice, std::unique_ptr<VulkanApiWrapper::SwapchainCreateInfoBuilder>(
            new VulkanApiWrapper::ConcurrentSwapchainCreateInfoBuilder(targetDevice.getDeviceHandle(),
                                                                       surface->getHandler(), 0))
    );

    std::vector<VkImageView> swapChainImageViews;
    swapChainImageViews.resize(swapChain.getSwapChainImages().size());
    for (size_t i = 0; i < swapChain.getSwapChainImages().size(); i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChain.getSwapChainImages()[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = swapChain.getFormat();
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        if (auto result = vkCreateImageView(logicalDevice->getHandler(), &createInfo, nullptr, &swapChainImageViews[i]);
                result != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }

    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(logicalDevice->getHandler(), imageView, nullptr);
    }
    ////////////////////////////////////////////////////////////////////////
}