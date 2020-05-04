#ifndef RECURVIS_PHYSICALDEVICE_H
#define RECURVIS_PHYSICALDEVICE_H

#include <vector>
#include <optional>
#include "Instance.h"

struct VkPhysicalDevice_T;

namespace VulkanApiWrapper {
    struct QueueFamily;

    struct PhysicalDeviceFeatures {
        bool robustBufferAccess;
        bool fullDrawIndexUint32;
        bool imageCubeArray;
        bool independentBlend;
        bool geometryShader;
        bool tessellationShader;
        bool sampleRateShading;
        bool dualSrcBlend;
        bool logicOp;
        bool multiDrawIndirect;
        bool drawIndirectFirstInstance;
        bool depthClamp;
        bool depthBiasClamp;
        bool fillModeNonSolid;
        bool depthBounds;
        bool wideLines;
        bool largePoints;
        bool alphaToOne;
        bool multiViewport;
        bool samplerAnisotropy;
        bool textureCompressionETC2;
        bool textureCompressionASTC_LDR;
        bool textureCompressionBC;
        bool occlusionQueryPrecise;
        bool pipelineStatisticsQuery;
        bool vertexPipelineStoresAndAtomics;
        bool fragmentStoresAndAtomics;
        bool shaderTessellationAndGeometryPointSize;
        bool shaderImageGatherExtended;
        bool shaderStorageImageExtendedFormats;
        bool shaderStorageImageMultisample;
        bool shaderStorageImageReadWithoutFormat;
        bool shaderStorageImageWriteWithoutFormat;
        bool shaderUniformBufferArrayDynamicIndexing;
        bool shaderSampledImageArrayDynamicIndexing;
        bool shaderStorageBufferArrayDynamicIndexing;
        bool shaderStorageImageArrayDynamicIndexing;
        bool shaderClipDistance;
        bool shaderCullDistance;
        bool shaderFloat64;
        bool shaderInt64;
        bool shaderInt16;
        bool shaderResourceResidency;
        bool shaderResourceMinLod;
        bool sparseBinding;
        bool sparseResidencyBuffer;
        bool sparseResidencyImage2D;
        bool sparseResidencyImage3D;
        bool sparseResidency2Samples;
        bool sparseResidency4Samples;
        bool sparseResidency8Samples;
        bool sparseResidency16Samples;
        bool sparseResidencyAliased;
        bool variableMultisampleRate;
        bool inheritedQueries;
    };

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
