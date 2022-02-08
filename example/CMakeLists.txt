cmake_minimum_required(VERSION 3.15)

project(urmem_example)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} urmem)