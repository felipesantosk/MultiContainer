cmake_minimum_required(VERSION 3.10)


project(CacheTest)

add_executable(${PROJECT_NAME} main.cpp test.cpp)

target_link_libraries(${PROJECT_NAME} CONAN_PKG::catch2)