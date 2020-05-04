#ifndef RECURVIS_GLFWAPP_H
#define RECURVIS_GLFWAPP_H

#include <string>
#include <vector>
#include "AbstractApp.hpp"
#include "GlfwWindow.h"
#include "Surface.h"

class GlfwApp : public AbstractApp {
    static bool initialized;

public:
    GlfwApp(std::string_view appName, const Version &appVersion);

    ~GlfwApp() override;

    std::shared_ptr<AbstractWindow> create_window(int w, int h) override;

    void main_loop() override;
};

std::vector<std::u8string> getRequiredVulkanExtensions();

#endif //RECURVIS_GLFWAPP_H
