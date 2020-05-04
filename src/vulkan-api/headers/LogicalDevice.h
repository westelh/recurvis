#ifndef RECURVIS_LOGICALDEVICE_H
#define RECURVIS_LOGICALDEVICE_H

#include <vector>
#include <vulkan/vulkan.h>
#include "PhysicalDevice.h"

namespace VulkanApiWrapper {
    class LogicalDevice {
        VkDevice handler{};

        std::vector<VkQueue> queues;

    public:
        LogicalDevice(const PhysicalDevice &physicalDevice, VkPhysicalDeviceFeatures featuresToUse,
                      const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfo,
                      const std::vector<std::u8string> &extensionsToUse);

        virtual ~LogicalDevice();

        [[nodiscard]] const VkDevice_T *getHandler() const;

        [[nodiscard]] const std::vector<VkQueue> &getQueues() const;
    };
}


#endif //RECURVIS_LOGICALDEVICE_H
