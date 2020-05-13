#include <Logger.h>
#include "InstanceBuilderDebug.h"

using namespace VAW;

InstanceBuilderDebug::InstanceBuilderDebug(std::unique_ptr<InstanceBuilder> &&ptr)
        : InstanceBuilder(), appGpuInstanceBuilder(std::move(ptr)) {
}

InstanceBuilderDebug::InstanceBuilderDebug(InstanceBuilderDebug &&move)
        : InstanceBuilder(), appGpuInstanceBuilder(std::move(move.appGpuInstanceBuilder)) {
}


InstanceBuilderDebug::~InstanceBuilderDebug() = default;

void InstanceBuilderDebug::setAppName() {
    appGpuInstanceBuilder->setAppName();
    if (appGpuInstanceBuilder->getAppName().has_value()) {
        RvLoggerDebugM("App name has set. value:{}",
                       recurvis::Logger::passWithoutCodeCvt(appGpuInstanceBuilder->getAppName().value()));
    } else {
        RvLoggerDebugM("App name ha not set yet!{}", "");
    }
    appName = appGpuInstanceBuilder->getAppName();
}

void InstanceBuilderDebug::setEngineName() {
    appGpuInstanceBuilder->setEngineName();
    if (appGpuInstanceBuilder->getEngineName().has_value()) {
        RvLoggerDebugM("Engine name has set. value:{}",
                       recurvis::Logger::passWithoutCodeCvt(appGpuInstanceBuilder->getEngineName().value()));
    } else {
        RvLoggerDebugM("Engine name has not set yet!{}", "");
    }
    engineName = appGpuInstanceBuilder->getEngineName();
}

void InstanceBuilderDebug::setAppVersion() {
    appGpuInstanceBuilder->setAppVersion();
    if (appGpuInstanceBuilder->getAppVersion().has_value()) {
        RvLoggerDebugM("App version has set. value:{}", to_string(appGpuInstanceBuilder->getAppVersion().value()));
    } else {
        RvLoggerDebugM("App version has not set yet!{}", "");
    }
    appVersion = appGpuInstanceBuilder->getAppVersion();
}

void InstanceBuilderDebug::setEngineVersion() {
    appGpuInstanceBuilder->setEngineVersion();
    if (appGpuInstanceBuilder->getEngineVersion().has_value()) {
        RvLoggerDebugM("Engine version has set. value:{}",
                       to_string(appGpuInstanceBuilder->getEngineVersion().value()));
    } else {
        RvLoggerDebugM("Engine version has not set yet!{}", "");
    }
    engineVersion = appGpuInstanceBuilder->getEngineVersion();
}

void InstanceBuilderDebug::setApiVersion() {
    appGpuInstanceBuilder->setApiVersion();
    if (appGpuInstanceBuilder->getApiVersion().has_value()) {
        RvLoggerDebugM("Api version has set. value:{}", to_string(appGpuInstanceBuilder->getApiVersion().value()));
    } else {
        RvLoggerDebugM("Api version has not set yet!{}", "");
    }
    apiVersion = appGpuInstanceBuilder->getApiVersion();
}

void InstanceBuilderDebug::setAllDeclaredLayers() {
    appGpuInstanceBuilder->setAllDeclaredLayers();
    if (appGpuInstanceBuilder->getAllDeclaredLayers().has_value()) {
        const auto &size = appGpuInstanceBuilder->getAllDeclaredLayers()->size();
        RvLoggerDebugM("{} Layers has set.", size);
        for (std::size_t i = 1; const auto &layer : appGpuInstanceBuilder->getAllDeclaredLayers().value()) {
            RvLoggerDebugM("Layer {} of {} is {}", i, size, recurvis::Logger::passWithoutCodeCvt(layer));
            RvLoggerDebugM("Check availability of layer {} => {}", recurvis::Logger::passWithoutCodeCvt(layer),
                           VAW::Instance::supportsLayer(layer));
            ++i;
        }
    } else {
        RvLoggerDebugM("Layers has not set yet!{}", "");
    }
    allDeclaredLayers = appGpuInstanceBuilder->getAllDeclaredLayers();
}

void InstanceBuilderDebug::setAllDeclaredExtensions() {
    appGpuInstanceBuilder->setAllDeclaredExtensions();
    if (auto extensions = appGpuInstanceBuilder->getAllDeclaredExtensions(); extensions.has_value()) {
        const auto &size = extensions->size();
        RvLoggerDebugM("{} extensions has set", size);
        for (auto i = 1; const auto &extension : extensions.value()) {
            RvLoggerDebugM("Extension {} of {} is {}", i, size, recurvis::Logger::passWithoutCodeCvt(extension));
            RvLoggerDebugM("Check availability of extension {} => {}", recurvis::Logger::passWithoutCodeCvt(extension),
                           VAW::Instance::supportsExtension(extension));
            for (const auto &availableLayer : Instance::enumerateAvailableLayerNames()) {
                RvLoggerDebugM("Check Availability of extension {} on layer {} => {}",
                               recurvis::Logger::passWithoutCodeCvt(extension),
                               recurvis::Logger::passWithoutCodeCvt(availableLayer),
                               Instance::supportsExtensionOnLayer(extension, availableLayer)
                );
            }
            ++i;
        }
    } else {
        RvLoggerDebugM("Extensions has not set yet!{}", "");
    }
}

Instance InstanceBuilderDebug::build() {
    auto &&build = appGpuInstanceBuilder->build();
    RvLoggerDebugM("Vulkan Instance was successfully created!{}", "");
    return std::move(build);
}

std::unique_ptr<InstanceBuilder> VAW::makeDebugBuilderFrom(std::unique_ptr<InstanceBuilder> &&origin) {
    return std::make_unique<InstanceBuilderDebug>(std::move(origin));
}
