cmake_minimum_required(VERSION 3.0.0)
project(FifthTask VERSION 0.1.0)

add_executable(FifthTask main.cpp)
add_subdirectory(./libraries)

target_link_libraries(${PROJECT_NAME} binFile)
target_link_libraries(${PROJECT_NAME} binarySearchTree)
target_link_libraries(${PROJECT_NAME} randomizedBinarySearchTree)
