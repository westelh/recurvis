#ifndef RECURVIS_IMAGEVIEW_H
#define RECURVIS_IMAGEVIEW_H

#include <memory>
#include <vulkan/vulkan.h>

namespace VulkanApiWrapper {
    class LogicalDevice;

    class ImageView {
    public:
        ImageView(std::shared_ptr<LogicalDevice> device, VkImageViewCreateInfo createInfo);

        ImageView(const ImageView &) = delete;

        ImageView(ImageView &&move) noexcept;

        ImageView &operator=(const ImageView &) = delete;

        ImageView &operator=(ImageView &&move) = delete;

        ~ImageView();

    private:
        std::shared_ptr<LogicalDevice> device;

        VkImageView handler{};
    };
}

#endif //RECURVIS_IMAGEVIEW_H
