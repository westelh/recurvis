#ifndef RECURVIS_INSTANCE_H
#define RECURVIS_INSTANCE_H

#include <vector>
#include <tuple>
#include <Version.h>

// TODO:Add flag support

namespace VulkanApiWrapper {
    class Instance {
    public:
        Instance(const Version &appVersion, const Version &engineVersion, const Version &apiVersion,
                 const std::u8string &appName, const std::u8string &engineName,
                 const std::vector<std::u8string> &layers, const std::vector<std::u8string> &extensions);

        Instance(Instance &&) noexcept;

        virtual ~Instance();

        explicit Instance(const Instance &) = delete;

        Instance &operator=(const Instance &) = delete;

        Instance operator=(Instance &&) = delete;

        [[nodiscard]] VkInstance getHandler() const noexcept;

        static size_t countAvailableLayers();

        static std::vector<VkLayerProperties> enumerateAvailableLayers();

        static std::vector<std::u8string> enumerateAvailableLayerNames();

        static size_t countAvailableInstanceExtensions();

        static std::vector<VkExtensionProperties> enumerateAvailableInstanceExtensions();

        static std::vector<std::u8string> enumerateAvailableInstanceExtensionNames();

        static std::size_t countAvailableInstanceExtensionsOnLayer(const std::optional<std::u8string> &layerName);

        static std::vector<VkExtensionProperties>
        enumerateAvailableInstanceExtensionsOnLayer(const std::optional<std::u8string> &layerName);

        static std::vector<std::u8string>
        enumerateAvailableInstanceExtensionNamesOnLayer(const std::optional<std::u8string> &layerName);

        static bool supportsLayer(std::u8string_view layerName);

        static bool supportsExtension(std::u8string_view extensionName);

        static bool
        supportsExtensionOnLayer(std::u8string_view extensionName, const std::optional<const std::u8string> &layerName);

    private:
        VkInstance handler;

        // リソースの寿命を保証するため必要
        class InternalInstanceBuilder {
        public:
            InternalInstanceBuilder(const Version &appVersion, const Version &engineVersion, const Version &apiVersion,
                                    std::u8string appName, std::u8string engineName,
                                    std::vector<std::u8string> allDeclaredLayers,
                                    std::vector<std::u8string> allDeclaredExtensions);

            VkInstance build();

        private:
            uint32_t appVersion;

            uint32_t engineVersion;

            uint32_t apiVersion;

            std::u8string appName;

            std::u8string engineName;

            VkApplicationInfo applicationInfo;

            std::vector<std::u8string> allDeclaredLayers;

            std::vector<const char *> pStrAllDeclaredLayers;

            std::vector<std::u8string> allDeclaredExtensions;

            std::vector<const char *> pStrAllDeclaredExtensions;

            VkInstanceCreateInfo instanceCreateInfo;
        };
    };
}

#endif //RECURVIS_INSTANCE_H