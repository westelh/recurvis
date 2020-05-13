#ifndef RECURVIS_INSTANCEBUILDER_H
#define RECURVIS_INSTANCEBUILDER_H

#include <string>
#include <vector>
#include <optional>
#include <vulkan/vulkan.h>
#include "Instance.h"

namespace VAW {
    class InstanceBuilder {
    public:
        virtual void setAppName() = 0;

        virtual void setEngineName() = 0;

        virtual void setAppVersion() = 0;

        virtual void setEngineVersion() = 0;

        virtual void setApiVersion() = 0;

        virtual void setAllDeclaredLayers() = 0;

        virtual void setAllDeclaredExtensions() = 0;

        const std::optional<Version> &getAppVersion() const;

        const std::optional<Version> &getEngineVersion() const;

        const std::optional<Version> &getApiVersion() const;

        const std::optional<std::u8string> &getAppName() const;

        const std::optional<std::u8string> &getEngineName() const;

        const std::optional<std::vector<std::u8string>> &getAllDeclaredLayers() const;

        const std::optional<std::vector<std::u8string>> &getAllDeclaredExtensions() const;

        virtual Instance build();

        InstanceBuilder() = default;

        virtual ~InstanceBuilder() = default;

    protected:
        std::optional<Version> appVersion;

        std::optional<Version> engineVersion;

        std::optional<Version> apiVersion;

        std::optional<std::u8string> appName;

        std::optional<std::u8string> engineName;

        std::optional<std::vector<std::u8string>> allDeclaredLayers;

        std::optional<std::vector<std::u8string>> allDeclaredExtensions;
    };
}

#endif //RECURVIS_INSTANCEBUILDER_H
