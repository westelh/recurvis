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
find_package(OpenGL REQUIRED)

#############################
# SPDLOG configuration
#############################
add_subdirectory(3rd/spdlog)

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
        -Wall -Wextra -Werror -pedantic -Wno-error=uninitialized
        $<$<CONFIG:RELEASE>:-Ofast>
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:DEBUG>:-O0>
        $<$<CONFIG:DEBUG>:-ggdb3>
)
add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
        $<$<CONFIG:RELEASE>:BOOST_DISABLE_ASSERTS>
)

set(UI_SRCDIR ${CMAKE_SOURCE_DIR}/src/ui)
set(UI_CPPDIR ${UI_SRCDIR}/cpp)
set(UI_HEADERS_DIR ${UI_SRCDIR}/headers)

set(MAIN_SRCDIR ${CMAKE_SOURCE_DIR}/src/main)
set(MAIN_CPPDIR ${MAIN_SRCDIR}/cpp)
set(MAIN_HEADERS_DIR ${MAIN_SRCDIR}/headers)

add_library(ui STATIC
        ${UI_HEADERS_DIR}/window_interface.hpp
        ${UI_HEADERS_DIR}/app_interface.hpp
        ${UI_CPPDIR}/window_interface.cpp
        src/ui/cpp/opengl_app.cpp
        src/ui/headers/opengl_app.h
        src/ui/cpp/opengl_window.cpp
        src/ui/headers/opengl_window.h
        src/ui/cpp/glfw_error.cpp
        src/ui/headers/glfw_error.h
        src/ui/headers/glfw_with_vulkan.h)

target_include_directories(ui
        PUBLIC ${UI_HEADERS_DIR}
        )

target_link_libraries(ui glfw OpenGL::GL spdlog::spdlog)
if (APPLE)
    target_link_libraries(ui MoltenVK)
endif ()

add_executable(main
        ${MAIN_CPPDIR}/main.cpp
        )
target_link_libraries(main ui ${ALLEGRO_LINK_LIBRARIES} ${METAL_LIBRARY} ${IOSURFACE_LIBRARY} ${QUARTZCORE_LIBRARY})