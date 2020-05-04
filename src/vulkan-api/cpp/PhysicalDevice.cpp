#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "util.h"
#include "PhysicalDevice.h"

using namespace VulkanApiWrapper;
using namespace recurvis;

namespace {
    VkPhysicalDeviceProperties queryDeviceProperty(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties ret;
        vkGetPhysicalDeviceProperties(device, &ret);
        return ret;
    }

    VkPhysicalDeviceFeatures queryAvailableFeatures(VkPhysicalDevice device) {
        VkPhysicalDeviceFeatures ret;
        vkGetPhysicalDeviceFeatures(device, &ret);
        return ret;
    }

    std::vector<VkExtensionProperties> queryAvailableDeviceExtensions(VkPhysicalDevice device) {
        uint32_t extCount = 0;
        if (vkEnumerateDeviceExtensionProperties(device, nullptr, &extCount, nullptr) != VK_SUCCESS)
            spdlog::error("Querying device extensions count failed!");
        std::vector<VkExtensionProperties> extensions{extCount};
        if (vkEnumerateDeviceExtensionProperties(device, nullptr, &extCount, extensions.data()) != VK_SUCCESS)
            spdlog::error("Device extensions enumeration failed!");
        return extensions;
    }

    std::vector<VkQueueFamilyProperties> queryAvailableQueueFamilies(VkPhysicalDevice device) {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        return queueFamilies;
    }

    std::vector<QueueFamily> queryAvailableQueueFamiliesConverted(VkPhysicalDevice device) {
        auto families = queryAvailableQueueFamilies(device);
        std::vector<QueueFamily> ret;
        std::size_t i = 0;
        for (const auto &family : families) {
            QueueFamily converted{
                    static_cast<uint32_t>(i),
                    family.queueCount,
                    family.queueFlags
            };
            ret.push_back(converted);
        }
        return ret;
    }
}

PhysicalDevice::PhysicalDevice(VkPhysicalDevice_T *vkPhysicalDevice)
        : device_handle(vkPhysicalDevice),
          property(queryDeviceProperty(device_handle)),
          availableFeatures(queryAvailableFeatures(device_handle)),
          availableDeviceExtensions(queryAvailableDeviceExtensions(device_handle)),
          availableQueueFamilies(queryAvailableQueueFamiliesConverted(device_handle)) {
}

PhysicalDevice::PhysicalDevice(const PhysicalDevice &d)
        : device_handle(d.getDeviceHandle()),
          property(d.property),
          availableFeatures(d.availableFeatures),
          availableDeviceExtensions(d.availableDeviceExtensions),
          availableQueueFamilies(d.availableQueueFamilies) {

}

PhysicalDevice::PhysicalDevice(PhysicalDevice &&d) noexcept
        : device_handle(d.device_handle),
          property(d.property),
          availableFeatures(d.availableFeatures),
          availableDeviceExtensions(d.availableDeviceExtensions),
          availableQueueFamilies(d.availableQueueFamilies) {

}

std::vector<QueueFamily> PhysicalDevice::getQueueFamilyProperties() const {
    return availableQueueFamilies;
}

const VkPhysicalDeviceFeatures &PhysicalDevice::getAvailableFeatures() const noexcept {
    return availableFeatures;
}

std::optional<std::vector<QueueFamily>> PhysicalDevice::getSuitableQueueFamilies(unsigned int flag) const {
    auto families = getQueueFamilyProperties();
    if (families.empty()) return std::nullopt;

    std::vector<QueueFamily> ret;
    for (auto &family: families) {
        if ((family.flag & flag) == flag) {
            ret.push_back(family);
        }
    }
    if (ret.empty()) return std::nullopt;
    else return ret;
}

VkPhysicalDevice_T *PhysicalDevice::getDeviceHandle() const {
    return device_handle;
}

std::u8string_view PhysicalDevice::getName() const {
    return reinterpret_cast<const char8_t *>(property.deviceName);
}

std::vector<PhysicalDevice> PhysicalDevice::availableDevices(const Instance &instance) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance.getHandler(), &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(instance.getHandler(), &deviceCount, physicalDevices.data());
    std::vector<PhysicalDevice> ret;
    for (const auto &physicalDevice : physicalDevices) {
        PhysicalDevice d(physicalDevice);
        spdlog::debug("Device {} found", removeUTF8Assurance(d.getName()));
        ret.emplace_back(d);
    }
    return ret;
}

const std::vector<VkExtensionProperties> &PhysicalDevice::getAvailableDeviceExtensions() const {
    return availableDeviceExtensions;
}

bool QueueFamily::supportsGraphics() const noexcept {
    return flag & VK_QUEUE_GRAPHICS_BIT;
}

bool QueueFamily::supportsCompute() const noexcept {
    return flag & VK_QUEUE_COMPUTE_BIT;
}

bool QueueFamily::supportsTransfer() const noexcept {
    return flag & VK_QUEUE_TRANSFER_BIT;
}

bool QueueFamily::supportsSparseBinding() const noexcept {
    return flag & VK_QUEUE_SPARSE_BINDING_BIT;
}

bool QueueFamily::supportsProtectedMemory() const noexcept {
    return flag & VK_QUEUE_PROTECTED_BIT;
}
