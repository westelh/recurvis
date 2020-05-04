#ifndef APP_INTERFACE_H
#define APP_INTERFACE_H

#include <memory>
#include <vector>
#include <list>
#include "spdlog/spdlog.h"
#include "Version.h"
#include "AbstractWindow.hpp"

class AbstractApp {
private:
    const Version appVersion;

    const std::string appName;

    AbstractWindow::window_updater updater;

    std::list<std::shared_ptr<AbstractWindow>> windows;

protected:
    bool should_exit_loop();

    int update_all_windows();

    // Remove from list and destroy windows
    std::size_t remove_closing_windows();

    virtual std::shared_ptr<AbstractWindow> create_window(int w, int h) = 0;

public:
    AbstractApp(const Version &appVersion, std::string_view appName);

    virtual ~AbstractApp() = default;

    [[nodiscard]] Version getAppVersion() const;

    [[nodiscard]] const std::string &getAppName() const;

    std::shared_ptr<AbstractWindow> add_window(int w, int h);

    [[nodiscard]] const std::list<std::shared_ptr<AbstractWindow>> &getWindows() const;

    [[nodiscard]] AbstractWindow::window_updater &getUpdater();

    virtual void main_loop() = 0;
};

#endif