cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0076 NEW) # CMakeが自動的に相対パスを絶対パスへ変換する
project(recurvis CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
option(BUILD_TESTS OFF)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/3rd/googletest)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed")
endif()

set(CMAKE_CXX_STANDARD 20) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

# On windows, remove lib prefix
if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()


if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(${GTEST_DIR}/googletest)
    add_executable(singletonTest src/test/singletonTest.cpp)
    #target_link_libraries(singletonTest singleton gtest_main)
    target_link_libraries(singletonTest gtest_main)
    add_test(singletonTest singletonTest)
endif()

#############################
# GLFW configuration
#############################
#Disable needless modules
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#Add to cmake builds
add_subdirectory(3rd/glfw)

#############################
# Vulkan
#############################
find_package(Vulkan REQUIRED)

#############################
# SPDLOG configuration
#############################
find_package(spdlog REQUIRED)

#############################
# MoltenVK configuration (macOS only)
#############################
if (APPLE)
    set(MoltenVK_SDK_ROOT "~" CACHE STRING "where is MoltenVK?")
    add_library(MoltenVK STATIC IMPORTED)
    set_target_properties(MoltenVK PROPERTIES IMPORTED_LOCATION ${MoltenVK_SDK_ROOT}/MoltenVK/macOS/static/libMoltenVK.a)
    set_target_properties(MoltenVK PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${MoltenVK_SDK_ROOT}/MoltenVK/include)

    find_library(IOSURFACE_LIBRARY IOSurface)
    find_library(METAL_LIBRARY Metal)
    find_library(QUARTZCORE_LIBRARY QuartzCore)
    set_target_properties(MoltenVK PROPERTIES INTERFACE_LINK_LIBRARIES ${IOSURFACE_LIBRARY})
    set_target_properties(MoltenVK PROPERTIES INTERFACE_LINK_LIBRARIES ${METAL_LIBRARY})
    set_target_properties(MoltenVK PROPERTIES INTERFACE_LINK_LIBRARIES ${QUARTZCORE_LIBRARY})
endif ()

# Compiler options
add_compile_options(
        -Wall
        -Wextra
        -Werror
        -pedantic
        $<$<CONFIG:RELEASE>:-Ofast>
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:DEBUG>:-O0>
        $<$<CONFIG:DEBUG>:-ggdb3>
        $<$<CXX_COMPILER_ID:Clang>:-fchar8_t>
)
add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
        $<$<CONFIG:RELEASE>:BOOST_DISABLE_ASSERTS>
)

add_library(util
        src/util/cpp/Version.cpp
        src/util/headers/Version.h
        src/util/headers/Logger.h src/util/cpp/Logger.cpp)
target_include_directories(util
        PUBLIC src/util/headers
        )
target_link_libraries(util spdlog::spdlog)

add_library(vulkan_api STATIC
        src/vulkan-api/cpp/LogicalDevice.cpp
        src/vulkan-api/cpp/PhysicalDevice.cpp
        src/vulkan-api/cpp/Instance.cpp
        src/vulkan-api/headers/Instance.h
        src/vulkan-api/headers/LogicalDevice.h
        src/vulkan-api/headers/PhysicalDevice.h
        src/vulkan-api/headers/util.h
        src/vulkan-api/cpp/VulkanError.cpp
        src/vulkan-api/headers/VulkanError.h
        src/vulkan-api/cpp/util.cpp
        src/vulkan-api/headers/InstanceBuilder.h
        src/vulkan-api/cpp/InstanceBuilder.cpp
        src/vulkan-api/headers/InstanceBuilderDirector.h
        src/vulkan-api/cpp/InstanceBuilderDirector.cpp
        src/vulkan-api/headers/InstanceBuilderDebug.h
        src/vulkan-api/cpp/InstanceBuilderDebug.cpp
        #        src/vulkan-api/headers/LogicalDeviceBuilder.h
        #        src/vulkan-api/headers/LogicalDeviceBuilderDefault.h
        #        src/vulkan-api/cpp/LogicalDeviceBuilderDefault.cpp
        #        src/vulkan-api/headers/QueueRequestBuilder.h
        #        src/vulkan-api/cpp/QueueRequestBuilder.cpp
        #        src/vulkan-api/headers/QueueHabitat.h
        #        src/vulkan-api/cpp/QueueHabitat.cpp
        #        src/vulkan-api/cpp/LogicalDeviceBuilder.cpp
        )
target_include_directories(vulkan_api
        PUBLIC src/vulkan-api/headers
        )
target_link_libraries(vulkan_api
        PRIVATE util
        PRIVATE spdlog::spdlog
        PRIVATE Vulkan::Vulkan)

add_library(ui STATIC
        src/ui/headers/AbstractWindow.hpp
        src/ui/headers/AbstractApp.hpp
        src/ui/cpp/window_interface.cpp
        src/ui/cpp/GlfwApp.cpp
        src/ui/headers/GlfwApp.h
        src/ui/cpp/GlfwWindow.cpp
        src/ui/headers/GlfwWindow.h
        src/ui/cpp/glfw_error.cpp
        src/ui/headers/glfw_error.h
        src/ui/headers/glfw_with_vulkan.h
        src/ui/cpp/AbstractApp.cpp
        src/ui/headers/API_Implement.h
        src/ui/cpp/API_Implement.cpp
        src/ui/cpp/Surface.cpp
        src/ui/headers/Surface.h
        src/ui/cpp/VulkanSurface.cpp
        src/ui/headers/internal/VulkanSurface.h
        src/ui/cpp/AbstractGpuInstance.cpp
        src/ui/headers/AbstractGpuInstance.h
        src/ui/cpp/VulkanGpuInstance.cpp
        src/ui/headers/VulkanGpuInstance.h
        src/ui/cpp/AppGpuInstanceBuilder.cpp
        src/ui/headers/internal/AppGpuInstanceBuilder.h)
target_include_directories(ui
        PUBLIC src/ui/headers
        PRIVATE src/ui/headers/internal
        )
target_link_libraries(ui
        PUBLIC glfw
        PUBLIC Vulkan::Vulkan
        PRIVATE util
        PRIVATE spdlog::spdlog
        PRIVATE vulkan_api
        )

add_executable(main src/main/cpp/main.cpp)

target_link_libraries(main
        ui
        spdlog::spdlog
        util
        $<$<PLATFORM_ID:Darwin>:${METAL_LIBRARY}>
        $<$<PLATFORM_ID:Darwin>:${IOSURFACE_LIBRARY}>
        $<$<PLATFORM_ID:Darwin>:${QUARTZCORE_LIBRARY}>

        # lerning
        # TODO:delete this needless dependency
        vulkan_api
        )