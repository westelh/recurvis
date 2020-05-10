#ifndef RECURVIS_LOGICALDEVICE_H
#define RECURVIS_LOGICALDEVICE_H

#include <vector>
#include <vulkan/vulkan.h>
#include "PhysicalDevice.h"

// TODO: add method that returns which extensions are enabled

namespace VulkanApiWrapper {
    class LogicalDevice {
        VkDevice handler{};

        std::vector<VkQueue> queues;

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
    };
}


#endif //RECURVIS_LOGICALDEVICE_H
