#ifndef RECURVIS_LOGICALDEVICE_H
#define RECURVIS_LOGICALDEVICE_H

#include <vector>
#include <vulkan/vulkan.h>
#include "PhysicalDevice.h"

namespace VulkanApiWrapper {
    class LogicalDevice {
    public:
        LogicalDevice(const PhysicalDevice &physicalDevice, VkPhysicalDeviceFeatures featuresToUse,
                      const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfo,
                      const std::vector<std::u8string> &extensionsToUse);

        LogicalDevice(const LogicalDevice &) = delete;

        LogicalDevice(LogicalDevice &&) = delete;

        LogicalDevice &operator=(const LogicalDevice &) = delete;

        LogicalDevice &operator=(LogicalDevice &&) = delete;

        virtual ~LogicalDevice();

        [[nodiscard]] VkDevice_T *getHandler() const;

        [[nodiscard]] const std::vector<VkQueue> &getQueues() const;

        [[nodiscard]] std::vector<std::u8string_view> getEnabledExtensions() const noexcept;

        [[nodiscard]] bool checkIfExtensionEnabled(std::u8string_view extensionName) const noexcept;

    private:
        VkDevice handler{};

        std::vector<VkQueue> queues;

        std::vector<std::u8string> enabledExtensions;
    };
}


#endif //RECURVIS_LOGICALDEVICE_H
