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

set(CMAKE_CXX_STANDARD 17) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

# On windows, remove lib prefix
if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

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

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(${GTEST_DIR}/googletest)
    add_executable(singletonTest src/test/singletonTest.cpp)
    #target_link_libraries(singletonTest singleton gtest_main)
    target_link_libraries(singletonTest gtest_main)
    add_test(singletonTest singletonTest)
endif()

#find_package(PkgConfig)
#pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_main-5)

set(UI_SRCDIR ${CMAKE_SOURCE_DIR}/src/ui)
set(UI_CPPDIR ${UI_SRCDIR}/cpp)
set(UI_HEADERS_DIR ${UI_SRCDIR}/headers)

set(MAIN_SRCDIR ${CMAKE_SOURCE_DIR}/src/main)
set(MAIN_CPPDIR ${MAIN_SRCDIR}/cpp)
set(MAIN_HEADERS_DIR ${MAIN_SRCDIR}/headers)

add_library(ui STATIC
        ${UI_HEADERS_DIR}/window.hpp
        ${UI_HEADERS_DIR}/app_interface.hpp
        ${UI_HEADERS_DIR}/allegro_window.hpp
        ${UI_HEADERS_DIR}/allegro_app.hpp
        ${UI_CPPDIR}/window.cpp
        ${UI_CPPDIR}/allegro_window.cpp
        ${UI_CPPDIR}/allegro_app.cpp
        )

target_include_directories(ui
        PRIVATE ${ALLEGRO_INCLUDE_DIRS}
        PUBLIC ${UI_HEADERS_DIR}
        )

#target_link_libraries(ui allegro-5)
target_link_libraries(ui ${ALLEGRO_LINK_LIBRARIES})

add_executable(main
    ${MAIN_CPPDIR}/main.cpp
)
target_link_libraries(main ui ${ALLEGRO_LINK_LIBRARIES})