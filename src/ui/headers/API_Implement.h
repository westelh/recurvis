#ifndef RECURVIS_API_IMPLEMENT_H
#define RECURVIS_API_IMPLEMENT_H

#include <memory>
#include "AbstractApp.hpp"

std::shared_ptr<AbstractApp> getVulkanApp(std::string_view appName, const Version &appVersion);

#endif //RECURVIS_API_IMPLEMENT_H
