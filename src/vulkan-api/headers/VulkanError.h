#ifndef RECURVIS_VULKANERROR_H
#define RECURVIS_VULKANERROR_H

#include <stdexcept>
#include <map>
#include <string>
#include <vulkan/vulkan.h>

class VulkanError : public std::exception {
    static std::map<VkResult, std::string> names;

    const VkResult code;

public:
    explicit VulkanError(VkResult code);

    [[nodiscard]] VkResult getCode() const;

    [[nodiscard]] const char *what() const noexcept override;
};


#endif //RECURVIS_VULKANERROR_H
