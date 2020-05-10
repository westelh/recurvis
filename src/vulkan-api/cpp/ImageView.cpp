#include <ImageView.h>

#include <utility>
#include "VulkanError.h"
#include "LogicalDevice.h"

using namespace VulkanApiWrapper;

ImageView::ImageView(std::shared_ptr<LogicalDevice> device_, VkImageViewCreateInfo createInfo) :
        device(std::move(device_)) {
    if (auto result = vkCreateImageView(device->getHandler(), &createInfo, nullptr, &handler); result != VK_SUCCESS) {
        throw VulkanError(result);
    }
}

ImageView::ImageView(ImageView &&move) noexcept:
        device(std::move(move.device)),
        handler(move.handler) {
    move.handler = nullptr;
}

ImageView::~ImageView() {
    if (handler) {
        vkDestroyImageView(device->getHandler(), this->handler, nullptr);
    }
}

