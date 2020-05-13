#include "InstanceBuilder.h"
#include "InstanceBuilderDirector.h"

using namespace VAW;

InstanceBuilderDirector::InstanceBuilderDirector(std::unique_ptr<InstanceBuilder> &&builder_) : builder(
        std::move(builder_)) {
}

Instance InstanceBuilderDirector::construct() {
    builder->setAppName();
    builder->setEngineName();
    builder->setAppVersion();
    builder->setEngineVersion();
    builder->setApiVersion();
    builder->setAllDeclaredLayers();
    builder->setAllDeclaredExtensions();
    return builder->build();
}

