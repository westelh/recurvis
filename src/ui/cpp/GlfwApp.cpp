#include <sstream>
#include <cstdlib>
#include <array>
#include "spdlog/spdlog.h"
#include "glfw_with_vulkan.h"
#include "glfw_error.h"
#include "Version.h"
#include "PhysicalDevice.h"
#include "GlfwApp.h"
#include "LogicalDevice.h"
#include "GlfwWindow.h"
#include "Instance.h"

using namespace std::string_literals;
using namespace VAW;

bool GlfwApp::initialized = false;

GlfwApp::GlfwApp(std::string_view appName, const Version &appVersion) :
        AbstractApp(appVersion, appName) {

    if (initialized) return;

    if (!glfwInit()) throw glfw_error::since_last_call();

    if (!glfwVulkanSupported()) throw glfw_error::since_last_call();

    initialized = true;
}

std::shared_ptr<AbstractWindow> GlfwApp::create_window(int w, int h) {
    auto &&window = std::make_shared<GlfwWindow>(w, h);
    return std::dynamic_pointer_cast<AbstractWindow>(window);
}

GlfwApp::~GlfwApp() {
    glfwTerminate();
}

void GlfwApp::main_loop() {
    while (!should_exit_loop()) {
        remove_closing_windows();
        update_all_windows();
        std::this_thread::sleep_for(AbstractWindow::wait);
    }
}

std::vector<std::u8string> getRequiredVulkanExtensions() {
    uint32_t count = 0;
    glfwGetRequiredInstanceExtensions(&count);
    std::vector<std::u8string> ret(count);
    const char8_t **lowStr = reinterpret_cast<const char8_t **>(glfwGetRequiredInstanceExtensions(&count));
    for (std::size_t i = 0; i < count; ++i) {
        ret.at(i) = lowStr[i];
    }
    return ret;
}
