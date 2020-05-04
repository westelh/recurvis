#ifndef RECURVIS_APPGPUINSTANCEBUILDER_H
#define RECURVIS_APPGPUINSTANCEBUILDER_H

#include <memory>
#include "InstanceBuilder.h"

class AbstractApp;

class AppGpuInstanceBuilder : public VulkanApiWrapper::InstanceBuilder {
private:
    std::shared_ptr<AbstractApp> app;

    std::vector<std::u8string> layersRequest;

    std::vector<std::u8string> extensionsRequest;

public:
    explicit AppGpuInstanceBuilder(std::shared_ptr<AbstractApp> app, std::vector<std::u8string> layers,
                                   std::vector<std::u8string> extensions);

    void setAppName() override;

    void setEngineName() override;

    void setAppVersion() override;

    void setEngineVersion() override;

    void setApiVersion() override;

    void setAllDeclaredLayers() override;

    void setAllDeclaredExtensions() override;

    const std::vector<std::u8string> &getLayersRequest() const;

    void setLayersRequest(const std::vector<std::u8string> &vector);

    const std::vector<std::u8string> &getExtensionsRequest() const;

    void setExtensionsRequest(const std::vector<std::u8string> &vector);
};

#endif //RECURVIS_APPGPUINSTANCEBUILDER_H
