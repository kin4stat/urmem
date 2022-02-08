cmake_minimum_required (VERSION 3.15)

project("urmem")

OPTION(BUILD_EXAMPLES "Build the examples" OFF)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

if (BUILD_EXAMPLES)
    add_subdirectory(example)
endif()