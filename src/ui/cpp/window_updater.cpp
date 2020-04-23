#include "window_updater.h"

#include <utility>

window_updater::window_updater(const std::shared_ptr<window_interface>& w)
: windows(),
loop_continue(true) {

windows.push_back(w);

}

void window_updater::updater() {
    while (!windows.empty()) {
        auto iter = windows.begin();
        for (auto& item : windows) {
            if (item->is_closing()) {
                windows.erase(iter);
                break;
            }

            item->update();

            ++iter;
        }
    }
}

window_updater::~window_updater() {
}
