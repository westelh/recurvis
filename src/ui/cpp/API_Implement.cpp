#include "API_Implement.h"
#include "GlfwApp.h"

std::shared_ptr<AbstractApp> getVulkanApp(std::string_view appName, const Version &appVersion) {
    return std::shared_ptr<AbstractApp>(new GlfwApp(appName, appVersion));
}
