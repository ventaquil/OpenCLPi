cmake_minimum_required(VERSION 3.7)
project(OpenCLPi)

set(SOURCE_FILES main.cpp)

find_package(OpenCL REQUIRED)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main OpenCL::OpenCL)
