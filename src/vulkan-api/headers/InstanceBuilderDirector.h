#ifndef INSTANCEBUILDERDIRECTOR_H
#define INSTANCEBUILDERDIRECTOR_H

#include <memory>
#include <vulkan/vulkan.h>
#include "Instance.h"

namespace VAW {
    class InstanceBuilder;

    class InstanceBuilderDirector {
    public:
        explicit InstanceBuilderDirector(std::unique_ptr<InstanceBuilder> &&builder);

        Instance construct();

    private:
        std::unique_ptr<InstanceBuilder> builder;
    };
}

#endif //INSTANCEBUILDERDIRECTOR_H