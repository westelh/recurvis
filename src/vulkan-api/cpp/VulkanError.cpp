#include <sstream>
#include "VulkanError.h"

using namespace std::literals::string_literals;

std::map<VkResult, std::string> VulkanError::names = {
        {VK_SUCCESS,                                            "SUCCESS"s},
        {VK_NOT_READY,                                          "NOT_READY"s},
        {VK_TIMEOUT,                                            "TIMEOUT"s},
        {VK_EVENT_SET,                                          "EVENT SET"s},
        {VK_EVENT_RESET,                                        "EVENT_RESET"s},
        {VK_INCOMPLETE,                                         "INCOMPLETE"s},
        {VK_ERROR_OUT_OF_HOST_MEMORY,                           "ERROR_OUT_OF_HOST_MEMORY"s},
        {VK_ERROR_OUT_OF_DEVICE_MEMORY,                         "ERROR_OUT_OF_DEVICE_MEMORY"s},
        {VK_ERROR_INITIALIZATION_FAILED,                        "ERROR_INITIALIZATION_FAILED"s},
        {VK_ERROR_DEVICE_LOST,                                  "ERROR_DEVICE_LOST"s},
        {VK_ERROR_MEMORY_MAP_FAILED,                            "ERROR_MEMORY_MAP_FAILED"s},
        {VK_ERROR_LAYER_NOT_PRESENT,                            "ERROR_LAYER_NOT_PRESENT"s},
        {VK_ERROR_EXTENSION_NOT_PRESENT,                        "ERROR_EXTENSION_NOT_PRESENT"s},
        {VK_ERROR_FEATURE_NOT_PRESENT,                          "ERROR_FEATURE_NOT_PRESENT"s},
        {VK_ERROR_INCOMPATIBLE_DRIVER,                          "ERROR_INCOMPATIBLE_DRIVER"s},
        {VK_ERROR_TOO_MANY_OBJECTS,                             "ERROR_TOO_MANY_OBJECTS"s},
        {VK_ERROR_FORMAT_NOT_SUPPORTED,                         "ERROR_FORMAT_NOT_SUPPORTED"s},
        {VK_ERROR_FRAGMENTED_POOL,                              "ERROR_FRAGMENTED_POOL"s},
        {VK_ERROR_UNKNOWN,                                      "ERROR_UNKNOWN"s},
        {VK_ERROR_OUT_OF_POOL_MEMORY,                           "ERROR_OUT_OF_POOL_MEMORY"s},
        {VK_ERROR_INVALID_EXTERNAL_HANDLE,                      "ERROR_INVALID_EXTERNAL_HANDLE"s},
        {VK_ERROR_FRAGMENTATION,                                "ERROR_FRAGMENTATION"s},
        {VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,               "ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"s},
        {VK_ERROR_SURFACE_LOST_KHR,                             "ERROR_SURFACE_LOST_KHR"s},
        {VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,                     "ERROR_NATIVE_WINDOW_IN_USE_KHR"s},
        {VK_SUBOPTIMAL_KHR,                                     "SUBOPTIMAL_KHR"s},
        {VK_ERROR_OUT_OF_DATE_KHR,                              "ERROR_OUT_OF_DATE_KHR"s},
        {VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,                     "ERROR_INCOMPATIBLE_DISPLAY_KHR"s},
        {VK_ERROR_VALIDATION_FAILED_EXT,                        "ERROR_VALIDATION_FAILED_EXT"s},
        {VK_ERROR_INVALID_SHADER_NV,                            "ERROR_INVALID_SHADER_NV"s},
        {VK_ERROR_INCOMPATIBLE_VERSION_KHR,                     "ERROR_INCOMPATIBLE_VERSION_KHR"s},
        {VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT, "ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT"s},
        {VK_ERROR_NOT_PERMITTED_EXT,                            "ERROR_NOT_PERMITTED_EXT"s},
        {VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT,          "ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT"s},
        {VK_THREAD_IDLE_KHR,                                    "THREAD_IDLE_KHR"s},
        {VK_THREAD_DONE_KHR,                                    "THREAD_DONE_KHR"s},
        {VK_OPERATION_DEFERRED_KHR,                             "OPERATION_DEFERRED_KHR"s},
        {VK_OPERATION_NOT_DEFERRED_KHR,                         "OPERATION_NOT_DEFERRED_KHR"s},
        {VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT,                "ERROR_PIPELINE_COMPILE_REQUIRED_EXT"s},
        {VK_ERROR_OUT_OF_POOL_MEMORY_KHR,                       "ERROR_OUT_OF_POOL_MEMORY_KHR"s},
        {VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR,                  "ERROR_INVALID_EXTERNAL_HANDLE_KHR"s},
        {VK_ERROR_FRAGMENTATION_EXT,                            "ERROR_FRAGMENTATION_EXT"s},
        {VK_ERROR_INVALID_DEVICE_ADDRESS_EXT,                   "ERROR_INVALID_DEVICE_ADDRESS_EXT"s},
        {VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR,           "ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR"s},
        {VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT,                "ERROR_PIPELINE_COMPILE_REQUIRED_EXT"s},
        {VK_RESULT_MAX_ENUM,                                    "RESULT_MAX_ENUM"s}
};

VulkanError::VulkanError(VkResult code_) : code(code_) {
}

VkResult VulkanError::getCode() const {
    return code;
}

const char *VulkanError::what() const noexcept {
    static const char *buffer;
    static std::stringstream ss;
    auto nameItr = names.find(getCode());
    if (nameItr == names.end()) {
        return "Unrecorded return code!";
    } else {
        ss << "Returned error code : " << nameItr->second;
        buffer = ss.str().c_str();
        return buffer;
    }
}
