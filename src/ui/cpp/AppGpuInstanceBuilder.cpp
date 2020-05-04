#include <utility>
#include "Logger.h"
#include "AbstractApp.hpp"
#include "AppGpuInstanceBuilder.h"

namespace {
    std::u8string unSafeApplyToUTF8(std::string_view str) noexcept {
        return std::u8string{reinterpret_cast<const char8_t *>(str.data())};
    }
}

AppGpuInstanceBuilder::AppGpuInstanceBuilder(std::shared_ptr<AbstractApp> app, std::vector<std::u8string> layers,
                                             std::vector<std::u8string> extensions)
        : app(std::move(app)),
          layersRequest(std::move(layers)),
          extensionsRequest(std::move(extensions)) {
}

void AppGpuInstanceBuilder::setAppName() {
    appName = unSafeApplyToUTF8(app->getAppName());
}

void AppGpuInstanceBuilder::setEngineName() {
    engineName = u8"recurvis UI engine";
}

void AppGpuInstanceBuilder::setAppVersion() {
    appVersion = app->getAppVersion();
}

void AppGpuInstanceBuilder::setEngineVersion() {
    engineVersion = Version(0, 0, 0);
}

void AppGpuInstanceBuilder::setApiVersion() {
    apiVersion = Version(0, 0, 0);
}

void AppGpuInstanceBuilder::setAllDeclaredLayers() {
    allDeclaredLayers = std::vector<std::u8string>{};
    allDeclaredLayers->reserve(layersRequest.size());
    for (const auto &layer : layersRequest) {
        allDeclaredLayers->push_back(layer);
    }
}

void AppGpuInstanceBuilder::setAllDeclaredExtensions() {
    allDeclaredExtensions = std::vector<std::u8string>{};
    allDeclaredExtensions->reserve(extensionsRequest.size());
    for (const auto &extension : extensionsRequest) {
        allDeclaredExtensions->push_back(extension);
    }
}

const std::vector<std::u8string> &AppGpuInstanceBuilder::getLayersRequest() const {
    return layersRequest;
}

void AppGpuInstanceBuilder::setLayersRequest(const std::vector<std::u8string> &vector) {
    AppGpuInstanceBuilder::layersRequest = vector;
}

const std::vector<std::u8string> &AppGpuInstanceBuilder::getExtensionsRequest() const {
    return extensionsRequest;
}

void AppGpuInstanceBuilder::setExtensionsRequest(const std::vector<std::u8string> &vector) {
    AppGpuInstanceBuilder::extensionsRequest = vector;
}




