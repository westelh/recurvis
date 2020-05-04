#ifndef RECURVIS_INSTANCEBUILDERDEBUG_H
#define RECURVIS_INSTANCEBUILDERDEBUG_H

#include "InstanceBuilder.h"

namespace VulkanApiWrapper {
    class InstanceBuilderDebug : public VulkanApiWrapper::InstanceBuilder {
    public:
        InstanceBuilderDebug(std::unique_ptr<InstanceBuilder> &&appGpuInstanceBuilder);

        InstanceBuilderDebug(InstanceBuilderDebug &&move);

        ~InstanceBuilderDebug();

        void setAppName() override;

        void setEngineName() override;

        void setAppVersion() override;

        void setEngineVersion() override;

        void setApiVersion() override;

        void setAllDeclaredLayers() override;

        void setAllDeclaredExtensions() override;

        VulkanApiWrapper::Instance build() override;

    private:
        std::unique_ptr<InstanceBuilder> appGpuInstanceBuilder;
    };

    std::unique_ptr<InstanceBuilder> makeDebugBuilderFrom(std::unique_ptr<InstanceBuilder> &&origin);
}


#endif //RECURVIS_INSTANCEBUILDERDEBUG_H
