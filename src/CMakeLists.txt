cmake_minimum_required(VERSION 3.10)

project(MultiContainerSrc)

add_library(${PROJECT_NAME} SHARED cache.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC MultiContainerInclude)
