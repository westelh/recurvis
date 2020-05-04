#include <algorithm>
#include <utility>
#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "util.h"
#include "VulkanError.h"
#include "Instance.h"

using namespace std::string_literals;
using namespace VulkanApiWrapper;
using namespace recurvis;

namespace {
    uint32_t makeVersionNumberFrom(Version v) {
        return VK_MAKE_VERSION(v.getMajor(), v.getMinor(), v.getPatch());
    }
}

Instance::Instance(const Version &appVersion, const Version &engineVersion, const Version &apiVersion,
                   const std::u8string &appName, const std::u8string &engineName,
                   const std::vector<std::u8string> &layers, const std::vector<std::u8string> &extensions)
        : handler() {
    InternalInstanceBuilder builder(appVersion, engineVersion, apiVersion, appName, engineName, layers, extensions);
    handler = builder.build();
}

Instance::Instance(Instance &&instance) noexcept: handler(instance.handler) {
    instance.handler = nullptr;
}

Instance::~Instance() {
    if (handler != nullptr) {
        spdlog::debug("Instance deleted");
        vkDestroyInstance(handler, nullptr);
    }
}

VkInstance Instance::getHandler() const noexcept {
    return handler;
}

size_t Instance::countAvailableLayers() {
    uint32_t count;
    if (auto result = vkEnumerateInstanceLayerProperties(&count, nullptr); result != VK_SUCCESS)
        throw VulkanError(result);
    return count;
}

std::vector<VkLayerProperties> Instance::enumerateAvailableLayers() {
    uint32_t count = countAvailableLayers();
    std::vector<VkLayerProperties> layers{count};
    if (auto result = vkEnumerateInstanceLayerProperties(&count, layers.data()); result != VK_SUCCESS)
        throw VulkanError(result);
    return layers;
}

size_t Instance::countAvailableInstanceExtensions() {
    return countAvailableInstanceExtensionsOnLayer(std::nullopt);
}

std::vector<VkExtensionProperties> Instance::enumerateAvailableInstanceExtensions() {
    return enumerateAvailableInstanceExtensionsOnLayer(std::nullopt);
}

std::size_t Instance::countAvailableInstanceExtensionsOnLayer(const std::optional<std::u8string> &layerName) {
    uint32_t count;
    const char *layerNamePtr = layerName.has_value() ? reinterpret_cast<const char *>(layerName->data()) : nullptr;
    if (auto result = vkEnumerateInstanceExtensionProperties(layerNamePtr, &count, nullptr); result != VK_SUCCESS)
        throw VulkanError(result);
    return count;
}

std::vector<VkExtensionProperties>
Instance::enumerateAvailableInstanceExtensionsOnLayer(const std::optional<std::u8string> &layerName) {
    auto count = static_cast<uint32_t>(countAvailableInstanceExtensionsOnLayer(layerName));
    std::vector<VkExtensionProperties> ret{count};
    const char *layerNamePtr = layerName.has_value() ? reinterpret_cast<const char *>(layerName->c_str()) : nullptr;
    if (auto result = vkEnumerateInstanceExtensionProperties(layerNamePtr, &count, ret.data()); result != VK_SUCCESS)
        throw VulkanError(result);
    return ret;
}

bool Instance::supportsLayer(std::u8string_view layerName) {
    auto available = enumerateAvailableLayers();
    return std::any_of(available.begin(), available.end(), [&layerName](const auto &availableItem) {
        return layerName == reinterpret_cast<const char8_t *>(availableItem.layerName);
    });
}

bool Instance::supportsExtension(const std::u8string_view extensionName) {
    return supportsExtensionOnLayer(extensionName, std::nullopt);
}

bool Instance::supportsExtensionOnLayer(const std::u8string_view extensionName,
                                        const std::optional<const std::u8string> &layerName) {
    auto available = enumerateAvailableInstanceExtensionsOnLayer(layerName);
    return std::any_of(available.begin(), available.end(), [&extensionName](const auto &item) {
        return extensionName == reinterpret_cast<const char8_t *>(item.extensionName);
    });
}

std::vector<std::u8string> Instance::enumerateAvailableLayerNames() {
    return recurvis::apply(enumerateAvailableLayers(), [](const auto &property) {
        return std::u8string(reinterpret_cast<const char8_t *>(property.layerName));
    });
}

std::vector<std::u8string> Instance::enumerateAvailableInstanceExtensionNames() {
    return recurvis::apply(enumerateAvailableInstanceExtensions(), [](const auto &property) {
        return std::u8string(reinterpret_cast<const char8_t *>(property.extensionName));
    });
}

std::vector<std::u8string>
Instance::enumerateAvailableInstanceExtensionNamesOnLayer(const std::optional<std::u8string> &layerName) {
    return recurvis::apply(enumerateAvailableInstanceExtensionsOnLayer(layerName), [](const auto &property) {
        return std::u8string(reinterpret_cast<const char8_t *>(property.extensionName));
    });
}

Instance::InternalInstanceBuilder::InternalInstanceBuilder(const Version &appVersion_,
                                                           const Version &engineVersion_,
                                                           const Version &apiVersion_,
                                                           std::u8string appName_,
                                                           std::u8string engineName_,
                                                           std::vector<std::u8string> allDeclaredLayers_,
                                                           std::vector<std::u8string> allDeclaredExtensions_)
        : appVersion(makeVersionNumberFrom(appVersion_)),
          engineVersion(makeVersionNumberFrom(engineVersion_)),
          apiVersion(makeVersionNumberFrom(apiVersion_)),
          appName(std::move(appName_)),
          engineName(std::move(engineName_)),
          applicationInfo(),
          allDeclaredLayers(std::move(allDeclaredLayers_)),
          pStrAllDeclaredLayers(recurvis::apply(allDeclaredLayers, [](const auto &resource) {
              return reinterpret_cast<const char *>(resource.c_str());
          })),
          allDeclaredExtensions(std::move(allDeclaredExtensions_)),
          pStrAllDeclaredExtensions(recurvis::apply(allDeclaredExtensions, [](const auto &resource) {
              return reinterpret_cast<const char *>(resource.c_str());
          })), instanceCreateInfo() {
    applicationInfo = VkApplicationInfo{
            VK_STRUCTURE_TYPE_APPLICATION_INFO,
            nullptr,
            reinterpret_cast<const char *>(appName.c_str()),
            appVersion,
            reinterpret_cast<const char *>(engineName.c_str()),
            engineVersion,
            apiVersion
    };
    instanceCreateInfo = VkInstanceCreateInfo{
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            nullptr,
            0,
            &applicationInfo,
            static_cast<uint32_t>(allDeclaredLayers.size()),
            pStrAllDeclaredLayers.data(),
            static_cast<uint32_t>(allDeclaredExtensions.size()),
            pStrAllDeclaredExtensions.data()
    };
}

VkInstance Instance::InternalInstanceBuilder::build() {
    VkInstance instance;
    if (auto result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance); result != VK_SUCCESS)
        throw VulkanError(result);
    return instance;
}
