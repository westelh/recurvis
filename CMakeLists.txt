cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0076 NEW) # CMakeが自動的に相対パスを絶対パスへ変換する
project(recurvis CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
option(BUILD_TESTS OFF)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/3rd/googletest-release-1.8.0)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed")
endif()

set(CMAKE_CXX_STANDARD 17) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

# On windows, remove lib prefix
if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Compiler options
if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -march=native")
    set(CMAKE_CXX_RELEASE_FLAGS "-O2")
    set(CMAKE_CXX_DEBUG_FLAGS "-g3 -fsanitize=leak -fsanitise=address")
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(${GTEST_DIR}/googletest)
    add_executable(singletonTest src/test/singletonTest.cpp)
    target_link_libraries(singletonTest singleton gtest_main)
    add_test(singletonTest singletonTest)
endif()

find_package(PkgConfig)
pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_main-5)

set(MAIN_SRCDIR ${CMAKE_SOURCE_DIR}/src/main)

add_executable(main
    ${MAIN_SRCDIR}/main.cpp
    ${MAIN_SRCDIR}/window.cpp
    ${MAIN_SRCDIR}/allegro_app.cpp
    ${MAIN_SRCDIR}/allegro_window.cpp
)

message(${ALLEGRO_INCLUDE_DIRS})
target_include_directories(main
    PUBLIC
        ${MAIN_SRCDIR}/headers
        ${ALLEGRO_INCLUDE_DIRS}
)

message(${ALLEGRO_LINK_LIBRARIES})
target_link_libraries(main 
    ${ALLEGRO_LINK_LIBRARIES}
)