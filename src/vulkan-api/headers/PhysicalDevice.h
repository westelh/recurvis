#ifndef RECURVIS_PHYSICALDEVICE_H
#define RECURVIS_PHYSICALDEVICE_H

#include <vector>
#include <optional>
#include "Instance.h"

struct VkPhysicalDevice_T;

namespace VulkanApiWrapper {
    struct QueueFamily;

    class PhysicalDevice {
        VkPhysicalDevice_T *const device_handle;

        const VkPhysicalDeviceProperties property;

        const VkPhysicalDeviceFeatures availableFeatures;

        const std::vector<VkExtensionProperties> availableDeviceExtensions;

        const std::vector<QueueFamily> availableQueueFamilies;

        [[nodiscard]] std::vector<QueueFamily> getQueueFamilyProperties() const;

    public:
        explicit PhysicalDevice(VkPhysicalDevice_T *vkPhysicalDevice);

        PhysicalDevice(const PhysicalDevice &);

        PhysicalDevice(PhysicalDevice &&) noexcept;

        [[nodiscard]] std::u8string_view getName() const;

        [[nodiscard]] const VkPhysicalDeviceFeatures &getAvailableFeatures() const noexcept;

        [[nodiscard]] const std::vector<VkExtensionProperties> &getAvailableDeviceExtensions() const;

        [[nodiscard]] std::optional<std::vector<QueueFamily>> getSuitableQueueFamilies(unsigned int flag) const;

        [[nodiscard]] VkPhysicalDevice_T *getDeviceHandle() const;

        static std::vector<PhysicalDevice> availableDevices(const Instance &instance);
    };

    struct QueueFamily {
        uint32_t index;
        uint32_t capableQueueCount;
        uint32_t flag;

        [[nodiscard]] bool supportsGraphics() const noexcept;

        [[nodiscard]] bool supportsCompute() const noexcept;

        [[nodiscard]] bool supportsTransfer() const noexcept;

        [[nodiscard]] bool supportsSparseBinding() const noexcept;

        [[nodiscard]] bool supportsProtectedMemory() const noexcept;
    };
}

#endif //RECURVIS_PHYSICALDEVICE_H
