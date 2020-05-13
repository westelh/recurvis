#include "util.h"
#include "InstanceBuilder.h"

using namespace VAW;

Instance VAW::InstanceBuilder::build() {
    return Instance(appVersion.value(),
                    engineVersion.value(),
                    apiVersion.value(),
                    appName.value(),
                    engineName.value(),
                    allDeclaredLayers.value(),
                    allDeclaredExtensions.value());
}

const std::optional<Version> &InstanceBuilder::getAppVersion() const {
    return appVersion;
}

const std::optional<Version> &InstanceBuilder::getEngineVersion() const {
    return engineVersion;
}

const std::optional<Version> &InstanceBuilder::getApiVersion() const {
    return apiVersion;
}

const std::optional<std::u8string> &InstanceBuilder::getAppName() const {
    return appName;
}

const std::optional<std::u8string> &InstanceBuilder::getEngineName() const {
    return engineName;
}

const std::optional<std::vector<std::u8string>> &InstanceBuilder::getAllDeclaredLayers() const {
    return allDeclaredLayers;
}

const std::optional<std::vector<std::u8string>> &InstanceBuilder::getAllDeclaredExtensions() const {
    return allDeclaredExtensions;
}

