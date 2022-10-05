cmake_minimum_required(VERSION 3.0.0)

project(ThirdTask VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(./libraries)

target_link_libraries(${PROJECT_NAME} hashFunctions)
