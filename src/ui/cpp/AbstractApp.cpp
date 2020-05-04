#include "AbstractApp.hpp"

bool AbstractApp::should_exit_loop() {
    return windows.empty();
}

int AbstractApp::update_all_windows() {
    std::for_each(windows.begin(), windows.end(), [this](std::shared_ptr<AbstractWindow> &w) {
        updater.update(w);
    });
    return windows.size();
}

std::size_t AbstractApp::remove_closing_windows() {
    auto size_before = windows.size();
    windows.remove_if([](const std::shared_ptr<AbstractWindow> &w) {
        return w->is_closing();
    });
    auto removed = size_before - windows.size();
    if (removed > 0) {
        spdlog::info("{} window was removed", removed);
    }
    return removed;
}

AbstractApp::AbstractApp(const Version &appVersion, std::string_view appName) :
        appVersion(appVersion),
        appName(appName),
        updater(),
        windows() {

}

std::shared_ptr<AbstractWindow> AbstractApp::add_window(int w, int h) {
    auto &&win = create_window(w, h);
    windows.push_back(win);
    return std::move(win);
}

[[nodiscard]] AbstractWindow::window_updater &AbstractApp::getUpdater() {
    return updater;
}

Version AbstractApp::getAppVersion() const {
    return appVersion;
}

const std::string &AbstractApp::getAppName() const {
    return appName;
}

const std::list<std::shared_ptr<AbstractWindow>> &AbstractApp::getWindows() const {
    return windows;
}
