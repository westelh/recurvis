#include <algorithm>
#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "util.h"
#include "LogicalDevice.h"

using namespace VulkanApiWrapper;
using namespace recurvis;

namespace {
    int sumQueueCountFrom(const std::vector<VkDeviceQueueCreateInfo> &info) {
        int sum = 0;
        for (const auto &item : info) {
            sum += item.queueCount;
        }
        return sum;
    }

    bool checkDeviceExtensionSupport(const PhysicalDevice &physicalDevice, std::u8string_view extName) {
        auto supported = physicalDevice.getAvailableDeviceExtensions();
        return std::any_of(supported.begin(), supported.end(), [&extName](const VkExtensionProperties &prop) {
            return extName == reinterpret_cast<const char8_t *>(prop.extensionName);
        });
    }

    VkDevice createDevice(const PhysicalDevice &physicalDevice, VkPhysicalDeviceFeatures featuresRequest,
                          const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfo,
                          std::vector<std::u8string> extensionRequest) {

        //<editor-fold desc="Check extension availability">
        {
            for (const auto &extRequest : extensionRequest) {
                if (!checkDeviceExtensionSupport(physicalDevice, extRequest)) {
                    spdlog::error("Extension:{} is not supported on {}. Removed from request.",
                                  removeUTF8Assurance(extRequest), removeUTF8Assurance(physicalDevice.getName()));
                    extensionRequest.erase(std::find(extensionRequest.begin(), extensionRequest.end(), extRequest));
                }
            }
        }
        //</editor-fold>

        //<editor-fold desc="Device creation">
        {
            VkDevice handler;

            auto convertedRequest = recurvis::apply(extensionRequest,
                                                    [](const std::u8string &str) { return reinterpret_cast<const char *>(str.c_str()); });
            VkDeviceCreateInfo deviceCreateInfo{
                    VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                    nullptr,
                    0,
                    static_cast<uint32_t>(queueCreateInfo.size()),
                    queueCreateInfo.data(),
                    0,
                    nullptr,
                    static_cast<uint32_t>(extensionRequest.size()),
                    convertedRequest.data(),
                    &featuresRequest
            };
            VkResult result = vkCreateDevice(physicalDevice.getDeviceHandle(), &deviceCreateInfo, nullptr, &handler);
            if (result != VK_SUCCESS) {
                switch (result) {
                    case VK_ERROR_EXTENSION_NOT_PRESENT:
                        spdlog::critical("Extension not present!");
                        break;
                    case VK_ERROR_FEATURE_NOT_PRESENT:
                        spdlog::critical("Feature not present!");
                        break;
                    default:
                        spdlog::critical("Uncaught result code was returned!");
                }
                spdlog::critical("Failed to create logical device!");
                throw std::runtime_error("Failed to create logical device!");
            }
            spdlog::debug("Logical device was successfully created on {}",
                          removeUTF8Assurance(physicalDevice.getName()));

            return handler;
        }
        //</editor-fold>
    }

    std::vector<VkQueue> createQueues(VkDevice device, const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfo) {
        std::vector<VkQueue> queues{static_cast<std::size_t>(sumQueueCountFrom(queueCreateInfo))};
        spdlog::debug("{} queue creation request accepted", queueCreateInfo.size());
        for (const auto &info : queueCreateInfo) {
            for (std::size_t i = 0; i < info.queueCount; ++i) {
                vkGetDeviceQueue(device, info.queueFamilyIndex, i, &queues[i]);
                spdlog::debug("{} of {} requested queue created (family:{})", i + 1, info.queueCount,
                              info.queueFamilyIndex);
            }
        }
        return queues;
    }
}

LogicalDevice::LogicalDevice(const PhysicalDevice &physicalDevice, VkPhysicalDeviceFeatures featuresToUse,
                             const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfo,
                             const std::vector<std::u8string> &extensionsToUse)
        : handler{createDevice(physicalDevice, featuresToUse, queueCreateInfo, extensionsToUse)},
          queues(createQueues(handler, queueCreateInfo)) {
    enabledExtensions = extensionsToUse;
}

LogicalDevice::~LogicalDevice() {
    vkDestroyDevice(handler, nullptr);
}

const std::vector<VkQueue> &LogicalDevice::getQueues() const {
    return queues;
}

VkDevice_T *LogicalDevice::getHandler() const {
    return handler;
}

std::vector<std::u8string_view> LogicalDevice::getEnabledExtensions() const noexcept {
    return recurvis::apply(enabledExtensions, [](const auto &item) -> std::u8string_view {
        return item;
    });
}

bool LogicalDevice::checkIfExtensionEnabled(std::u8string_view extensionName) const noexcept {
    const auto &&enabled = getEnabledExtensions();
    return std::find(enabled.begin(), enabled.end(), extensionName) != enabled.end();
}
